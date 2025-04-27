
`include "parameters.v"

//Website:https://dlbeer.co.nz/articles/i2c.html
//------------------jcyuan change------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//----------------------USAGE----------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//FOR WRITE----------------------------------------------

/*START
Master-to-slave: device address, R/W# = 0 (0xAA)
Master-to-slave: register index (0x03)
Master-to-slave: register data (0x57)
STOP*/

//FOR READ-----------------------------------------------

/*START
Master-to-slave: device address, R/W# = 0 (0xAA)
Master-to-slave: register index (0x03)
RESTART
Master-to-slave: device address, R/W# = 1 (0xAB)
Slave-to-master (not acked): register data (0x57)
STOP*/

//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
module i2c_control(
SCL,
SDA,
RST,
o_reg_SIGNAL_INPUT_CONFIG,
o_reg_EDGE_TRIGGER_CONFIG,
o_reg_TOT_WINDOW_SHORT,
o_reg_TOT_WINDOW_LONG,
o_reg_TOT_TRIGGER_CONFIG,
o_reg_FILTER_TRIGGER_CONFIG,
o_reg_TRIGGER_HANDLER_CONFIG,
o_reg_DAC_CONTROL_CONFIG,
i_reg_DAC_CURRENT_DATA,
o_reg_CONTROL_BYTE
);

input SCL,RST;//asynchronous reset input
inout SDA;


output reg [7:0] o_reg_SIGNAL_INPUT_CONFIG = `SIGNAL_INPUT_CONFIG_DEFAULT;
output reg [7:0] o_reg_EDGE_TRIGGER_CONFIG = `EDGE_TRIGGER_CONFIG_DEFAULT;
output reg [15:0] o_reg_TOT_WINDOW_SHORT = `TOT_WINDOW_SHORT_DEFAULT;
output reg [15:0] o_reg_TOT_WINDOW_LONG = `TOT_WINDOW_LONG_DEFAULT;
output reg [15:0] o_reg_TOT_TRIGGER_CONFIG = `TOT_TRIGGER_CONFIG_DEFAULT;
output reg [15:0] o_reg_FILTER_TRIGGER_CONFIG = `FILTER_TRIGGER_CONFIG_DEFAULT;
output reg [15:0] o_reg_TRIGGER_HANDLER_CONFIG = `TRIGGER_HANDLER_CONFIG_DEFAULT;
output reg [7:0] o_reg_CONTROL_BYTE = 0;

 
output reg [95:0] o_reg_DAC_CONTROL_CONFIG = 0;
input [15:0] i_reg_DAC_CURRENT_DATA;

parameter [2:0] STATE_IDLE      = 3'h0,//idle
                STATE_DEV_ADDR  = 3'h1,//the slave addr match
                STATE_READ      = 3'h2,//the op=read
                STATE_IDX_PTR   = 3'h3,//get the index of inner-register
                STATE_WRITE     = 3'h4;//write the data in the reg

reg             start_detect;
reg             start_resetter;

reg             stop_detect;
reg             stop_resetter;

reg [3:0]       bit_counter;//(from 0 to 8)9counters-> one byte=8bits and one ack=1bit
reg [7:0]       input_shift;
reg             master_ack;
reg [2:0]       state;

reg [7:0]       output_shift;
reg             output_control;
reg [7:0]       index_pointer;



parameter [6:0] device_address = 7'h55;
wire            start_rst = RST | start_resetter;//detect the START for one cycle
wire            stop_rst = RST | stop_resetter;//detect the STOP for one cycle
wire            lsb_bit = (bit_counter == 4'h7) && !start_detect;//the 8bits one byte data
wire            ack_bit = (bit_counter == 4'h8) && !start_detect;//the 9bites ack
wire            address_detect = (input_shift[7:1] == device_address);//the input address match the slave
wire            read_write_bit = input_shift[0];// the write or read operation 0=write and 1=read
wire            write_strobe = (state == STATE_WRITE) && ack_bit;//write state and finish one byte=8bits
assign          SDA = output_control ? 1'bz : 1'b0;
//---------------------------------------------
//---------------detect the start--------------
//---------------------------------------------
always @ (posedge start_rst or negedge SDA)
begin
        if (start_rst)
                start_detect <= 1'b0;
        else
                start_detect <= SCL;
end

always @ (posedge RST or posedge SCL)
begin
        if (RST)
                start_resetter <= 1'b0;
        else
                start_resetter <= start_detect;
end
//the START just last for one cycle of SCL



//---------------------------------------------
//---------------detect the stop---------------
//---------------------------------------------
always @ (posedge stop_rst or posedge SDA)
begin
        if (stop_rst)
                stop_detect <= 1'b0;
        else
                stop_detect <= SCL;
end

always @ (posedge RST or posedge SCL)
begin
        if (RST)
                stop_resetter <= 1'b0;
        else
                stop_resetter <= stop_detect;
end
//the STOP just last for one cycle of SCL
//don't need to check the RESTART,due to: a START before it is STOP,it's START;
//                                        a START before it is START,it's RESTART;
//the RESET and START combine can be recognise the RESTART,but it's doesn't matter



//---------------------------------------------
//---------------latch the data---------------
//---------------------------------------------
always @ (negedge SCL)
begin
        if (ack_bit || start_detect)
                bit_counter <= 4'h0;
        else
                bit_counter <= bit_counter + 4'h1;
end
//counter to 9(from 0 to 8), one byte=8bits and one ack
always @ (posedge SCL)
        if (!ack_bit)
                input_shift <= {input_shift[6:0], SDA};
//at posedge SCL the data is stable,the input_shift get one byte=8bits



//---------------------------------------------
//------------slave-to-master transfer---------
//---------------------------------------------
always @ (posedge SCL)
        if (ack_bit)
                master_ack <= ~SDA;//the ack SDA is low
//the 9th bits= ack if the SDA=1'b0 it's a ACK,



//---------------------------------------------
//------------state machine--------------------
//---------------------------------------------
always @ (posedge RST or negedge SCL)//jcyuan comment
begin
        if (RST)
                state <= STATE_IDLE;
        else if (start_detect)
                state <= STATE_DEV_ADDR;
        else if (ack_bit)//at the 9th cycle and change the state by ACK
        begin
                case (state)
                STATE_IDLE:
                        state <= STATE_IDLE;

                STATE_DEV_ADDR:
                        if (!address_detect)//addr don't match
                                state <= STATE_IDLE;
                        else if (read_write_bit)// addr match and operation is read
                                state <= STATE_READ;
                        else//addr match and operation is write
                                state <= STATE_IDX_PTR;

                STATE_READ:
                        if (master_ack)//get the master ack
                                state <= STATE_READ;
                        else//no master ack ready to STOP
                                state <= STATE_IDLE;

                STATE_IDX_PTR:
                        state <= STATE_WRITE;//get the index and ready to write

                STATE_WRITE:
                        state <= STATE_WRITE;//when the state is write the state
                endcase
        end
        //if don't write and master send a stop,need to jump idle
        //the stop_detect is the next cycle of ACK
        else if(stop_detect)//jcyuan add
                state <= STATE_IDLE;//jcyuan add
end

//---------------------------------------------
//------------Register transfers---------------
//---------------------------------------------

//-------------------for index----------------
always @ (posedge RST or negedge SCL)
begin
        if (RST)
                index_pointer <= 8'h00;
        // else if (stop_detect)
                // index_pointer <= 8'h00;
        else if (ack_bit)//at the 9th bit -ack, the input_shift has one bytes
        begin
                if (state == STATE_IDX_PTR) //at the state get the inner-register index
                        index_pointer <= input_shift;
                else//ready for next read/write;bulk transfer of a block of data
                        index_pointer <= index_pointer + 8'h01;
        end
end

//----------------for write---------------------------
//we only define 4 registers for operation
always @ (posedge RST or negedge SCL)
begin
        if (RST)
        begin
                // reg_00 <= 8'h20;
                // reg_01 <= 8'h30;
                // reg_02 <= 8'h40;
                // reg_03 <= 8'h50;
        end//the moment the input_shift has one byte=8bits
        else if (write_strobe) 
        begin
                case(index_pointer)
                8'h01: o_reg_SIGNAL_INPUT_CONFIG[7:0]  <= input_shift;
                8'h02: o_reg_EDGE_TRIGGER_CONFIG[7:0]  <= input_shift;
                8'h03: o_reg_TOT_WINDOW_SHORT[15:8]  <= input_shift;
                8'h04: o_reg_TOT_WINDOW_SHORT[7:0]  <= input_shift;
                8'h05: o_reg_TOT_WINDOW_LONG[15:8]  <= input_shift;
                8'h06: o_reg_TOT_WINDOW_LONG[7:0]  <= input_shift;
                8'h07: o_reg_TOT_TRIGGER_CONFIG[15:8]  <= input_shift;
                8'h08: o_reg_TOT_TRIGGER_CONFIG[7:0]  <= input_shift;
                8'h09: o_reg_FILTER_TRIGGER_CONFIG[15:8]  <= input_shift;
                8'h0B: o_reg_FILTER_TRIGGER_CONFIG[7:0]  <= input_shift;
                8'h0C: o_reg_TRIGGER_HANDLER_CONFIG[15:8]  <= input_shift;
                8'h0D: o_reg_TRIGGER_HANDLER_CONFIG[7:0]  <= input_shift;
                8'h0E: o_reg_DAC_CONTROL_CONFIG[95:88] <= input_shift;
                8'h0F: o_reg_DAC_CONTROL_CONFIG[87:80] <= input_shift;
                8'h10: o_reg_DAC_CONTROL_CONFIG[79:72] <= input_shift;
                8'h11: o_reg_DAC_CONTROL_CONFIG[71:64] <= input_shift;
                8'h12: o_reg_DAC_CONTROL_CONFIG[63:56] <= input_shift;
                8'h13: o_reg_DAC_CONTROL_CONFIG[55:48] <= input_shift;
                8'h14: o_reg_DAC_CONTROL_CONFIG[47:40] <= input_shift;
                8'h15: o_reg_DAC_CONTROL_CONFIG[39:32] <= input_shift;
                8'h16: o_reg_DAC_CONTROL_CONFIG[31:24] <= input_shift;
                8'h17: o_reg_DAC_CONTROL_CONFIG[23:16] <= input_shift;
                8'h18: o_reg_DAC_CONTROL_CONFIG[15:8] <= input_shift;
                8'h19: o_reg_DAC_CONTROL_CONFIG[7:0] <= input_shift;
                8'h20: o_reg_CONTROL_BYTE[7:0] <= input_shift;

                endcase
        end
end

//------------------------for read-----------------------
always @ (negedge SCL)
begin
        if (lsb_bit)//at one byte that can be load the output_shift
        begin
                case (index_pointer)
                8'h01: output_shift <= o_reg_SIGNAL_INPUT_CONFIG;
                8'h02: output_shift <= o_reg_EDGE_TRIGGER_CONFIG;
                8'h03: output_shift <= o_reg_TOT_WINDOW_SHORT[15:8];
                8'h04: output_shift <= o_reg_TOT_WINDOW_SHORT[7:0];
                8'h05: output_shift <= o_reg_TOT_WINDOW_LONG[15:8];
                8'h06: output_shift <= o_reg_TOT_WINDOW_LONG[7:0];
                8'h07: output_shift <= o_reg_TOT_TRIGGER_CONFIG[15:8];
                8'h08: output_shift <= o_reg_TOT_TRIGGER_CONFIG[7:0];
                8'h09: output_shift <= o_reg_FILTER_TRIGGER_CONFIG[15:8];
                8'h0A: output_shift <= o_reg_FILTER_TRIGGER_CONFIG[7:0];
                8'h0B: output_shift <= o_reg_TRIGGER_HANDLER_CONFIG[15:8];
                8'h0C: output_shift <= o_reg_TRIGGER_HANDLER_CONFIG[7:0];
                8'h0E: output_shift <= o_reg_DAC_CONTROL_CONFIG[95:88];
                8'h0F: output_shift <= o_reg_DAC_CONTROL_CONFIG[87:80];
                8'h10: output_shift <= o_reg_DAC_CONTROL_CONFIG[79:72];
                8'h11: output_shift <= o_reg_DAC_CONTROL_CONFIG[71:64];
                8'h12: output_shift <= o_reg_DAC_CONTROL_CONFIG[63:56];
                8'h13: output_shift <= o_reg_DAC_CONTROL_CONFIG[55:48];
                8'h14: output_shift <= o_reg_DAC_CONTROL_CONFIG[47:40];
                8'h15: output_shift <= o_reg_DAC_CONTROL_CONFIG[39:32];
                8'h16: output_shift <= o_reg_DAC_CONTROL_CONFIG[31:24];
                8'h17: output_shift <= o_reg_DAC_CONTROL_CONFIG[23:16];
                8'h18: output_shift <= o_reg_DAC_CONTROL_CONFIG[15:8];
                8'h19: output_shift <= o_reg_DAC_CONTROL_CONFIG[7:0];
                8'h1A: output_shift <= i_reg_DAC_CURRENT_DATA[15:8];
                8'h1B: output_shift <= i_reg_DAC_CURRENT_DATA[7:0];
                8'h20: output_shift <= o_reg_CONTROL_BYTE[7:0];
                endcase
        end
        else
                output_shift <= {output_shift[6:0], 1'b0};
                //once the shift it,after 8 times the output_shift=8'b0
                //the 9th bit is 0 for the RESTART for address match slave ACK
end


    // Modification should just return REG[index_pointer] on a flattened array.
    // Then if write_strobe then we allow the array to be written, otherwise we take any internals that may edit it.
    
//---------------------------------------------
//------------Output driver--------------------
//---------------------------------------------

always @ (posedge RST or negedge SCL)
begin
        if (RST)
                output_control <= 1'b1;
        else if (start_detect)
                output_control <= 1'b1;
        else if (lsb_bit)
        begin
                output_control <=
                    !(((state == STATE_DEV_ADDR) && address_detect) ||
                      (state == STATE_IDX_PTR) ||
                      (state == STATE_WRITE));
                //when operation is wirte
                //addr match gen ACK,the index get gen ACK,and write data gen ACK
        end
        else if (ack_bit)
        begin
                // Deliver the first bit of the next slave-to-master
                // transfer, if applicable.
                if (((state == STATE_READ) && master_ack) ||
                    ((state == STATE_DEV_ADDR) &&
                        address_detect && read_write_bit))
                        output_control <= output_shift[7];
                        //for the RESTART and send the addr ACK for 1'b0
                        //for the read and master ack both slave is pull down
                else
                        output_control <= 1'b1;
        end
        else if (state == STATE_READ)//for read send output shift to SDA
                output_control <= output_shift[7];
        else
                output_control <= 1'b1;
end
endmodule
