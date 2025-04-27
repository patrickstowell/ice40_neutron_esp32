
// Wishbone compatible I2C looper.
// Periodically sends the threshold commands to i2C chips.
// Address loop is hardcoded.

module wb_hv (
   // wishbone interface
   input         clk_i,
   input         rst_i,
   // input        	I2CACTIVE,
   // input [11:0]    HVTARGET,
   // input [11:0]     HVLIMIT,
   // input [15:0]   RAMPSPEED,
   // input [11:0]  THRESHOLD1,
   // input [11:0]  THRESHOLD2,
   // input [2:0] EEPROMCHOICE,
   input [95:0] DAC_CONTROL_CONFIG,
   // output reg [11:0] HVCURRENT,
   output reg [15:0] DAC_CURRENT_DATA,
   output [1:0] SCLLINES,
   output [1:0] SDALINES
);

   wire [95:0] DAC_CONTROL_CONFIG;
   // reg [15:0] DAC_CURRENT_DATA;

   reg [11:0] HVTARGET;
   reg [11:0] HVLIMIT;
   reg [15:0] RAMPSPEED;
   reg [11:0] THRESHOLD1;
   reg [11:0] THRESHOLD2;
   reg [2:0] EEPROMCHOICE;



   always @(posedge clk_i) begin
      HVTARGET <= DAC_CONTROL_CONFIG[15:0];
      HVLIMIT <= DAC_CONTROL_CONFIG[31:16];
      RAMPSPEED <= DAC_CONTROL_CONFIG[47:32];
      THRESHOLD1 <= DAC_CONTROL_CONFIG[63:48];
      THRESHOLD2 <= DAC_CONTROL_CONFIG[79:64];
      EEPROMCHOICE <= DAC_CONTROL_CONFIG[95:80];
      DAC_CURRENT_DATA[15:0] <= HVCURRENT;
   end   

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// PARAMETERS
   ///	
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   // `include "parameters.dat"
   
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// Wishbone Interface
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////   
   // reg [15:0] 		    r_dat_o = 0;
   // assign dat_o = r_dat_o;
   
   // wire 		    valid_cmd = !rst_i && stb_i;
   // wire 		    valid_write_cmd = valid_cmd && we_i;
   // wire 		    valid_read_cmd = valid_cmd && !we_i;
   
   // reg [7:0] 		    wb_cmd = 0;
   // wire [8:0] 		    wb_adr = adr_i[8:0];
    
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// WIshhbone Register Access
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   // reg 			       I2CACTIVE = 0;
   // reg [11:0] 		    HVTARGET = 0;
   // reg [11:0] 		    HVLIMIT = 1600;
   // reg [15:0]         RAMPSPEED = 1525;
   // reg [11:0] 		    THRESHOLD1 = 500;
   // reg [11:0] 		    THRESHOLD2 = 500;
   // reg [2:0] 		    EEPROMCHOICE = 3'b010;
   
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// HV UPDATE
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   reg [11:0] HVCURRENT = 1100;
   reg 	      HVENABLE = 1;
   
   reg [31:0] hvcounter = 1;
   
   always @(posedge clk_i) begin
      
      if (hvcounter < 78430) hvcounter <= hvcounter+1;
      else hvcounter <= 0;
      
      if (HVENABLE) begin
         if (hvcounter == 0) begin
            if (HVCURRENT < HVTARGET && HVCURRENT < HVLIMIT - 1) HVCURRENT <= HVCURRENT + 1;
            else if (HVCURRENT > HVTARGET) HVCURRENT <= HVCURRENT - 1;
            else HVCURRENT <= HVCURRENT;
   end 
      end else begin
      HVCURRENT <= 0;
      end
      
   end

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// I2C IO Core
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   wire I2CENABLE;
   reg [1:0] I2CLINES; 
   reg [15:0] I2CDATA12;
   reg [15:0] I2CDATA34;
   reg 	      SENDI2C = 0;
   I2C4BYTES i2cpmod(.CLK(clk_i),
                     .ENABLE(I2CENABLE),
                     .I2CLINES(I2CLINES),
                     .I2CDATA12(I2CDATA12),
                     .I2CDATA34(I2CDATA34),
                     .SCLLINES(SCLLINES),
                     .SDALINES(SDALINES));

   reg I2CACTIVEF = 1;
   assign I2CENABLE = I2CACTIVEF & SENDI2C;
   
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// I2C Update Loop
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   reg [26:0] i2clooper = 0;
   always @(posedge clk_i) begin
      
      i2clooper <= i2clooper + 1;
      
      case(i2clooper[26:22])	
	1: 
	  begin
	     I2CLINES <= 2;
	     I2CDATA12 <= {8'b11000000,EEPROMCHOICE,5'b00000};
	     I2CDATA34 <= {THRESHOLD1, 4'b0000};
	     SENDI2C <= 0;
	  end
	2: SENDI2C <= 1;
	3: SENDI2C <= 0;
	
	4: 
	  begin
	     I2CLINES <= 2;
	     I2CDATA12 <= {8'b11000010,EEPROMCHOICE,5'b00000};
             I2CDATA34 <= {THRESHOLD2, 4'b0000};
             SENDI2C	<= 0;
	  end
	5: SENDI2C <= 1;
	6: SENDI2C <= 0;

	7:
	  begin
             I2CLINES <= 1;
             I2CDATA12 <= {8'b11000000,EEPROMCHOICE,5'b00000};
             I2CDATA34 <= {HVCURRENT, 4'b0000};
             SENDI2C    <= 0;
          end
	8: SENDI2C <= 1;
	9: SENDI2C <= 0;

	
	
      endcase
   end

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   ///
   /// Debugging
   ///
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   //assign led2 = !SENDI2C;
   //assign led1 = !(HVCURRENT == HVTARGET);   

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
endmodule
