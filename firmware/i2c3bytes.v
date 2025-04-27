`ifndef I2C3BYTES_v
`define I2C3BYTES_v

// Brute force I2C BUS.
// Making sure clocks were in line
// when sending I2C data was a pain.
//
// This module brute forces it by turning a 3 byte long address,
// into a proper I2C stream for the SCL/SDA lines.
//
// I2CLINES is used to switch between what SCL/SDA wires are driven.
// This allows the module to handle multiple buses at once but access is slow.

// Author : p.stowell

// module I2C4BYTES
module I2C4BYTES(
        input 	      CLK,
        input 	      ENABLE,

	input  [1:0] I2CLINES,
	input  [15:0] I2CDATA12,
        input  [15:0] I2CDATA34,

	output [1:0] SCLLINES,
	output [1:0] SDALINES
	);

    // Brute Force I2C Protocol Streams
    localparam STARTOFFSET = 1;
    localparam ENDOFFSET = 2;
    localparam sclstart = 4'b1110;
    localparam sdastart = 4'b1100;
    localparam sclend = 4'b0111;
    localparam sdaend = 4'b0011;
    localparam scldelay = 4'b0000;
    localparam sclperiod = 4'b0110;
    localparam sdahigh = 4'b1111;
    localparam sdalow = 4'b0000;

    wire module0_active = 0; //(bits_to_send > 0) & I2CLINES[0];
    wire module1_active = (bits_to_send > 0); // & I2CLINES[1];
                           
    // assign SCLLINES[0] = (bits_to_send > 0) & I2CLINES[0] & ~scl_current[167];
    // assign SDALINES[0] = (bits_to_send > 0) & I2CLINES[0] & ~sda_current[167];
    // assign SCLLINES[1] = (bits_to_send > 0) & I2CLINES[1] & ~scl_current[167];
    // assign SDALINES[1] = (bits_to_send > 0) & I2CLINES[1] & ~sda_current[167];

                            
    assign SCLLINES[0] = ((bits_to_send > 0) & ~scl_current[167]) | !I2CLINES[0] | (bits_to_send == 0);
    assign SDALINES[0] = ((bits_to_send > 0) & ~sda_current[167]) | !I2CLINES[0] |  (bits_to_send == 0);
    assign SCLLINES[1] = ((bits_to_send > 0) & ~scl_current[167]) | !I2CLINES[1] |  (bits_to_send == 0);
    assign SDALINES[1] = ((bits_to_send > 0) & ~sda_current[167]) | !I2CLINES[1] |  (bits_to_send == 0);

                           
    // assign SCLLINES[0] = (module0_active & ~scl_current[167]) | !module0_active;
    // assign SDALINES[0] = (module0_active & ~sda_current[167]) | !module0_active;
    // assign SCLLINES[1] = (module1_active & ~scl_current[167]) | !module1_active;
    // assign SDALINES[1] = (module1_active & ~sda_current[167]) | !module1_active;


    reg [14:0] clkcounter = 0;
    wire I2CCLK = clkcounter[14];
    always @(posedge CLK) clkcounter <= clkcounter + 1;

    // ------------------------------------------------
    // WIRE CONFIG MODE
    // ------------------------------------------------
    reg [2:0] ENABLEr;  always @(posedge I2CCLK) ENABLEr <= {ENABLEr[1:0], ENABLE};
    wire ENABLE_risingedge = (ENABLEr[2:1]==2'b01);  // now we can detect SCK rising edges

    reg [10:0] bits_to_send = 0;
    reg [167:0]  sda_current = 0;
    reg [167:0]  scl_current = 0;

    always @(posedge I2CCLK) begin

        if (ENABLE_risingedge) begin
           bits_to_send <= 168;
           sda_current <= {
                           sdahigh,
                           sdahigh,
                           sdastart,
                           scldelay,
			   I2CDATA12[15] ? sdahigh : sdalow,
                           I2CDATA12[14] ? sdahigh : sdalow,
                           I2CDATA12[13] ? sdahigh : sdalow,
                           I2CDATA12[12] ? sdahigh : sdalow,
                           I2CDATA12[11] ? sdahigh : sdalow,
                           I2CDATA12[10] ? sdahigh : sdalow,
                           I2CDATA12[ 9] ? sdahigh : sdalow,
                           I2CDATA12[ 8] ? sdahigh : sdalow,
			   sdalow,
			   I2CDATA12[7] ? sdahigh : sdalow,
                           I2CDATA12[6] ? sdahigh : sdalow,
                           I2CDATA12[5] ? sdahigh : sdalow,
                           I2CDATA12[4] ? sdahigh : sdalow,
                           I2CDATA12[3] ? sdahigh : sdalow,
                           I2CDATA12[2] ? sdahigh : sdalow,
                           I2CDATA12[1] ? sdahigh : sdalow,
                           I2CDATA12[0] ? sdahigh : sdalow,
                           sdalow,
                           I2CDATA34[15] ? sdahigh : sdalow,
                           I2CDATA34[14] ? sdahigh : sdalow,
                           I2CDATA34[13] ? sdahigh : sdalow,
                           I2CDATA34[12] ? sdahigh : sdalow,
                           I2CDATA34[11] ? sdahigh : sdalow,
                           I2CDATA34[10] ? sdahigh : sdalow,
                           I2CDATA34[ 9] ? sdahigh : sdalow,
                           I2CDATA34[ 8] ? sdahigh : sdalow,
			   sdalow,
                           I2CDATA34[ 7] ? sdahigh : sdalow,
                           I2CDATA34[ 6] ? sdahigh : sdalow,
                           I2CDATA34[ 5] ? sdahigh : sdalow,
                           I2CDATA34[ 4] ? sdahigh : sdalow,
                           I2CDATA34[ 3] ? sdahigh : sdalow,
                           I2CDATA34[ 2] ? sdahigh : sdalow,
                           I2CDATA34[ 1] ? sdahigh : sdalow,
                           I2CDATA34[ 0] ? sdahigh : sdalow,
                           sdalow,
                           scldelay,
                           sdaend
                           };
            scl_current <= { sdahigh,
                             sdahigh,
                             sclstart,
                             scldelay,

			     sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,

                             sclperiod,
			     
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
			     
			     sclperiod,
			     
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,

			     sclperiod,
			     
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
                             sclperiod,
			     
                             sclperiod,
                             scldelay,
                             sclend};


        end
        else
        if  (bits_to_send > 0) begin
            scl_current <= {scl_current[166:0], 1'b1};
            sda_current <= {sda_current[166:0], 1'b1};
            bits_to_send <= bits_to_send - 1;
        end
        else
        if (bits_to_send == 0 || bits_to_send > 168)
        begin
            sda_current <= 168'b1;
            scl_current <= 168'b1;
            scl_current[167] <= 1;
            sda_current[167] <= 1;
        end
    end

endmodule
`endif
