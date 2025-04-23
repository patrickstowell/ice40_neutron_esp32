`define SYNTHESIS
`timescale 1ns / 1ps

module i2c_master_strobe_tb();

  initial
  begin
    $dumpfile("sims/i2c_master_strobe_tb.vcd");
    $dumpvars(0,i2c_master_strobe_tb);
    # 10000 $finish;
  end

  reg READ_MODE = 0;

  wire CLK_SLOW;
  wire RESET_SLOW;

  wire CLK_FAST;
  wire RESET_FAST;

  CLOCK_HANDLER clock_handler(
    CLK_SLOW,
    RESET_SLOW,
    CLK_FAST,
    RESET_FAST
  );

  // wire SCL;
  // wire SDA;
  // reg [63:0] i2cdata = 64'b1100110010101010000000001111111111001100101010100000000011111111;
  // i2c_register_sender i2c(
  //   .clk(CLK_FAST),
  //   .rst(RESET_FAST),
  //   .enable(1),
  //   .data_reg(i2cdata),
  //   .scl(SCL),
  //   .sda(SDA)



reg [7:0] SBADRI = 0;
reg [7:0] SBDATI = 0;
wire [7:0] SBDATO = 0;
wire SBACKO;
wire I2CIRQ;
wire I2CWKUP;
wire SCLI;
wire SCLO;
wire SCLOE;
wire SDAI;
wire SDAO;
wire SDAOE;
reg SBSTBI = 0;
reg  SBRWI = 0;
SB_I2C #(
  .I2C_SLAVE_INIT_ADDR("0b1111100001"),
  .BUS_ADDR74("0b0001")
) i2cInst0 (
  .SBCLKI(CLK_SLOW),
  .SBRWI(SBRWI),
  .SBSTBI(SBSTBI),
  .SBADRI0(SBADRI[0]),
  .SBADRI1(SBADRI[1]),
  .SBADRI2(SBADRI[2]),
  .SBADRI3(SBADRI[3]),
  .SBADRI4(SBADRI[4]),
  .SBADRI5(SBADRI[5]),
  .SBADRI6(SBADRI[6]),
  .SBADRI7(SBADRI[7]),
  .SBDATI0(SBDATI[0]),
  .SBDATI1(SBDATI[1]),
  .SBDATI2(SBDATI[2]),
  .SBDATI3(SBDATI[3]),
  .SBDATI4(SBDATI[4]),
  .SBDATI5(SBDATI[5]),
  .SBDATI6(SBDATI[6]),
  .SBDATI7(SBDATI[7]),
  .SBDATO0(SBDATO[0]),
  .SBDATO1(SBDATO[1]),
  .SBDATO2(SBDATO[2]),
  .SBDATO3(SBDATO[3]),
  .SBDATO4(SBDATO[4]),
  .SBDATO5(SBDATO[5]),
  .SBDATO6(SBDATO[6]),
  .SBDATO7(SBDATO[7]),
  .SBACKO(SBACKO),
  .I2CIRQ(),
  .I2CWKUP(),
  .SCLI(SCLI),
  .SCLO(SCLO),
  .SCLOE(SCLOE),
  .SDAI(SDAI),
  .SDAO(SDAO),
  .SDAOE(SDAOE)
);

defparam i2cInst0.I2C_SLAVE_INIT_ADDR = "0b1111100001"; 
defparam i2cInst0.BUS_ADDR74 = "0b0001";

localparam REG_ADDR_I2CCR0    = 4'b0000;
localparam REG_ADDR_I2CCR1    = 4'b1000;
localparam REG_ADDR_I2CCMDR   = 4'b1001;
localparam REG_ADDR_I2CBRLSB  = 4'b1010;
localparam REG_ADDR_I2CBRMSB  = 4'b1010;
localparam REG_ADDR_I2CSR     = 4'b1011;
localparam REG_ADDR_I2CTXDR   = 4'b1011;
localparam REG_ADDR_I2CRXDR   = 4'b1110;
localparam REG_ADDR_I2CGCDR   = 4'b1111;
localparam REG_ADDR_I2CADDR   = 4'b0011;
localparam REG_ADDR_I2CINTCR  = 4'b0111;
localparam REG_ADDR_I2CINTSR  = 4'b0110;

localparam STATE_INIT_I2CCR0 = 0;
localparam STATE_INIT_I2CCR1 = 1;
localparam STATE_INIT_I2CCMDR = 2;
localparam STATE_INIT_I2CBRLSB = 3; // 240
localparam STATE_INIT_I2CBRMSB = 4; // 0
localparam STATE_SET_TXDR = 5;
localparam STATE_SEND_BYTE = 7;
localparam STATE_GET_RXDR = 6;
localparam STATE_WAIT = 7;

reg [7:0] state_i2c = 0;
reg [7:0] next_state = 0;

reg [1:0] CLK_HALF = 0;

always @(posedge CLK_SLOW) begin
  CLK_HALF <= CLK_HALF + 1;
end

wire CLK_HALF_NEW = CLK_HALF[0];

reg [15:0] counter = 10;
always @(posedge CLK_SLOW)
   begin

      if (state_i2c != next_state) begin
        counter <= counter - (counter > 0);
        if (counter == 0) state_i2c <= next_state;
        
      end else begin
        counter <= 10;
      end 

      //default
      SBSTBI <= state_i2c != next_state;
      SBRWI <= state_i2c != next_state;

      case (state_i2c)
      STATE_INIT_I2CCR0 : begin 
         SBADRI <= REG_ADDR_I2CCR0;
         SBDATI <= 8'b00000000;
        //  SBRWI <= 1;
        //  SBSTBI <= 1;
         next_state <= STATE_INIT_I2CCR1;
      end
      STATE_INIT_I2CCR1 : begin 
         SBADRI <= REG_ADDR_I2CCR1;
         SBDATI <= 8'b10000000;
        //  SBSTBI <= 1;
        //  SBRWI <= 1;
        //  if(SBACKO == 1) begin
            // SBSTBI <= 0;
         next_state <= STATE_INIT_I2CBRMSB;
        //  end
      end
      STATE_INIT_I2CBRMSB : begin 
         SBADRI <= REG_ADDR_I2CBRMSB;
         SBDATI <= 8'b00000000;
        //  SBSTBI <= 1;
        //  SBRWI <= 1;
        //  if(SBACKO == 1) begin
            // SBSTBI <= 0;
            next_state <= STATE_INIT_I2CBRLSB;
        //  end
      end
      STATE_INIT_I2CBRLSB : begin 
         SBADRI <= REG_ADDR_I2CBRLSB;
         SBDATI <= 8'b11110000;
        //  SBSTBI <= 1;
        //  SBRWI <= 1;
        //  if(SBACKO == 1) begin
            // SBSTBI <= 0;
            next_state <= STATE_SET_TXDR;
        //  end
      end
      STATE_SET_TXDR : begin 
         SBADRI <= REG_ADDR_I2CBRLSB;
         SBDATI <= 8'b11001010;
        //  SBSTBI <= 1;
        //  SBRWI <= 1;
         if(SBACKO == 1) begin
            SBSTBI <= 0;
            next_state <= STATE_SEND_BYTE;
         end
      end
      STATE_SEND_BYTE : begin 
         SBADRI <= REG_ADDR_I2CCMDR;
         SBDATI <= 8'b11010000;
        //  SBSTBI <= 1;
        //  SBRWI <= 1;
         if(SBACKO == 1) begin
            SBSTBI <= 0;
            next_state <= STATE_WAIT;
         end
      end
      STATE_WAIT: begin
        next_state <= STATE_WAIT;
      end




      endcase
   end



endmodule


//opcodes:
//0x00 nop
//0x01 init
//0x02 write 32bits inverted
//0x04 write leds (8bits LSB)
//0x06 write vector, the computer will send 4 * 32bit values
//0x07 read vector, the fpga will send 4 * 32bit values

// `define SYNTHESIS
// `timescale 1ns / 1ps

// module i2c_master_strobe_tb();

// module top(input [3:0] SW, input clk, output LED_R, output LED_G, output LED_B, input SPI_SCK, input SPI_SS, input SPI_MOSI, output SPI_MISO, input [3:0] SW);

//    parameter NOP=0, INIT=1, WR_INVERTED=2, WR_LEDS=4, WR_VEC=6, RD_VEC=7;

//    //state machine parameters
//    parameter INIT_SPICR0=0, INIT_SPICR1=INIT_SPICR0+1, INIT_SPICR2=INIT_SPICR1+1, INIT_SPIBR=INIT_SPICR2+1, INIT_SPICSR=INIT_SPIBR+1,
//              SPI_WAIT_RECEPTION=INIT_SPICSR+1, SPI_READ_OPCODE=SPI_WAIT_RECEPTION+1, SPI_READ_LED_VALUE=SPI_READ_OPCODE+1,
//              SPI_READ_INIT=SPI_READ_LED_VALUE+1, SPI_SEND_DATA=SPI_READ_INIT+1, SPI_WAIT_TRANSMIT_READY=SPI_SEND_DATA+1,
//              SPI_TRANSMIT=SPI_WAIT_TRANSMIT_READY+1;

//    parameter SPI_ADDR_SPICR0 = 8'b00001000, SPI_ADDR_SPICR1 = 8'b00001001, SPI_ADDR_SPICR2 = 8'b00001010, SPI_ADDR_SPIBR = 8'b00001011,
//              SPI_ADDR_SPITXDR = 8'b00001101, SPI_ADDR_SPIRXDR = 8'b00001110, SPI_ADDR_SPICSR = 8'b00001111, SPI_ADDR_SPISR = 8'b00001100;

//    parameter COMMAND_SIZE=4;
//    reg [7:0] state_i2c;

//    //hw spi signals
//    reg spi_stb; //strobe must be set to high when read or write
//    reg spi_rw; //selects read or write (high = write)
//    reg [7:0] spi_adr; // address
//    reg [7:0] spi_dati; // data input
//    wire [7:0] spi_dato; // data output
//    wire spi_ack; //ack that the transfer is done (read valid or write ack)
//    //the miso/mosi signals are not used, because this module is set as a slave
//    wire spi_miso;
//    wire spi_mosi;
//    wire spi_sck;
//    wire spi_csn;

//    SB_SPI SB_SPI_inst(.SBCLKI(clk), .SBSTBI(spi_stb), .SBRWI(spi_rw),
//       .SBADRI0(spi_adr[0]), .SBADRI1(spi_adr[1]), .SBADRI2(spi_adr[2]), .SBADRI3(spi_adr[3]), .SBADRI4(spi_adr[4]), .SBADRI5(spi_adr[5]), .SBADRI6(spi_adr[6]), .SBADRI7(spi_adr[7]),
//       .SBDATI0(spi_dati[0]), .SBDATI1(spi_dati[1]), .SBDATI2(spi_dati[2]), .SBDATI3(spi_dati[3]), .SBDATI4(spi_dati[4]), .SBDATI5(spi_dati[5]), .SBDATI6(spi_dati[6]), .SBDATI7(spi_dati[7]),
//       .SBDATO0(spi_dato[0]), .SBDATO1(spi_dato[1]), .SBDATO2(spi_dato[2]), .SBDATO3(spi_dato[3]), .SBDATO4(spi_dato[4]), .SBDATO5(spi_dato[5]), .SBDATO6(spi_dato[6]), .SBDATO7(spi_dato[7]),
//       .SBACKO(spi_ack),
//       .MI(spi_miso), .SO(SPI_MISO),
//       .MO(spi_mosi), .SI(SPI_MOSI),
//       .SCKI(SPI_SCK), .SCSNI(SPI_SS)
//    );

//    reg [2:0] led;
//    reg is_spi_init; //waits the INIT command from the master

//    reg [7:0] counter_read; //count the bytes to read to form a command
//    reg [7:0] command_data[7:0]; //the command, saved as array of bytes

//    reg [7:0] counter_send; //counts the bytes to send
//    reg [7:0] data_to_send; //buffer for data to be written in send register

//    //regs for the "vector" commands
//    reg [7:0] data_vector[15:0]; //4*32bits = 16*8bits
//    reg [3:0] counter_vector;

//    //leds output
//    assign LED_R = ~led[0];
//    assign LED_G = ~led[1];
//    assign LED_B = ~led[2];

//    initial begin

//       spi_reset = 0;
//       spi_wr_en = 0;
//       spi_wr_data = 0;
//       spi_rd_ack = 0;

//       led = 0;

//       spi_stb = 0;
//       spi_rw = 0;
//       spi_adr = 0;
//       spi_dati = 0;

//       is_spi_init = 0;
//       counter_send = 0;
//       counter_vector = 0;

//       state_i2c = INIT_SPICR0;
//    end

//    always @(posedge clk)
//    begin

//       //default
//       spi_stb <= 0;

//       case (state_spi)
//       INIT_SPICR0 : begin //spi control register 0, nothing interesting for this case (delay counts)
//          spi_adr <= SPI_ADDR_SPICR0;
//          spi_dati <= 8'b00000000;
//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= INIT_SPICR1;
//          end
//       end
//       INIT_SPICR1 : begin //spi control register 1
//          spi_adr <= SPI_ADDR_SPICR1;
//          spi_dati <= 8'b10000000; //bit7: enable SPI
//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= INIT_SPICR2;
//          end
//       end
//       INIT_SPICR2 : begin //spi control register 2
//          spi_adr <= SPI_ADDR_SPICR2;
//          spi_dati <= 8'b00000001; //bit0: lsb first
//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= INIT_SPIBR;
//          end
//       end
//       INIT_SPIBR : begin //spi clock prescale
//          spi_adr <= SPI_ADDR_SPIBR;
//          spi_dati <= 8'b00000000; //clock divider => 1
//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= INIT_SPICSR;
//          end
//       end
//       INIT_SPICSR : begin //SPI master chip select register, absolutely no use as SPI module set as slave
//          spi_adr <= SPI_ADDR_SPICSR;
//          spi_dati <= 8'b00000000;
//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= SPI_WAIT_RECEPTION;
//             counter_read <= 0;
//          end
//       end
//       SPI_WAIT_RECEPTION : begin
//          spi_adr <= SPI_ADDR_SPISR; //status register
//          spi_stb <= 1;
//          spi_rw <= 0; //read
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= SPI_WAIT_RECEPTION;

//             //wait for bit3, tells that data is available
//             if (is_spi_init == 0 && spi_dato[3] == 1) begin
//                state_spi <= SPI_READ_INIT;
//             end

//             if (is_spi_init == 1 && spi_dato[3] == 1) begin
//                if(counter_send < 6) begin //can only send 6 bytes back
//                   state_spi <= SPI_WAIT_TRANSMIT_READY;
//                end else begin
//                   state_spi <= SPI_READ_OPCODE;
//                end
//             end
//          end
//       end
//       SPI_WAIT_TRANSMIT_READY: begin
//          spi_adr <= SPI_ADDR_SPISR; //status registers
//          spi_stb <= 1;
//          spi_rw <= 0; //read
//          if(spi_ack == 1) begin
//             spi_stb <= 0;

//             //bit 4 = TRDY, transmit ready
//             if (spi_dato[4] == 1) begin
//                state_spi <= SPI_TRANSMIT;
//             end
//          end
//       end
//       SPI_TRANSMIT: begin
//          spi_adr <= SPI_ADDR_SPITXDR;
//          if(counter_send == 0) begin
//             spi_dati <= 8'b01000000;
//          end else begin
//             spi_dati <= data_to_send;
//          end

//          spi_stb <= 1;
//          spi_rw <= 1;
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             counter_send <= counter_send + 1;

//             if (is_spi_init == 0) begin
//                state_spi <= SPI_READ_INIT;
//             end else begin
//                state_spi <= SPI_READ_OPCODE;
//             end
//          end
//       end
//       SPI_READ_INIT: begin
//          spi_adr <= SPI_ADDR_SPIRXDR; //read data register
//          spi_stb <= 1;
//          spi_rw <= 0; //read
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             state_spi <= SPI_WAIT_RECEPTION;
//             command_data[counter_read] <= spi_dato;

//             if(spi_dato == 8'h11)begin
//                counter_read <= 0;
//                is_spi_init <= 1;
//                counter_send <= 0;
//             end
//          end
//       end
//       SPI_READ_OPCODE: begin
//          spi_adr <= SPI_ADDR_SPIRXDR; //read data register
//          spi_stb <= 1;
//          spi_rw <= 0; //read
//          if(spi_ack == 1) begin
//             spi_stb <= 0;
//             counter_read <= counter_read + 1;

//             state_spi <= SPI_WAIT_RECEPTION;
//             command_data[counter_read] <= spi_dato;

//             if( counter_read == 0 ) begin
//                data_to_send <= spi_dato;
//             end else if( command_data[0] == WR_INVERTED )begin
//                data_to_send <= ~spi_dato;
//             end else if( command_data[0] == WR_LEDS )begin
//                data_to_send <= spi_dato; //sends back what was written
//             end else if( command_data[0] == WR_VEC )begin //send vec from host
//                if(counter_read < 5)begin //only 4 bytes after the opcode are useful
//                   data_vector[counter_vector] <= spi_dato;
//                   counter_vector <= counter_vector + 1;
//                end
//             end else if( command_data[0] == RD_VEC )begin //send vec to host
//                if(counter_read < 5)begin //only 4 bytes after the opcode are useful
//                   data_to_send <= data_vector[counter_vector];
//                   counter_vector <= counter_vector + 1;
//                end
//             end

//             if(counter_read == 7) begin
//                counter_read <= 0;
//                counter_send <= 0;
//                if( command_data[0] == WR_LEDS )begin
//                   led <= command_data[1][2:0]; //read the led value
//                end
//             end
//          end
//       end

//       endcase
//    end

// endmodule