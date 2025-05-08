`define SYNTHESIS
`timescale 1ns / 1ps

module i2c_sender_tb();

  initial
  begin
    $dumpfile("i2c_sender_tb.vcd");
    $dumpvars(0,i2c_sender_tb);
    # 1000000 $finish;
  end

  wire CLK_SLOW;
  wire CLK_SLOW_GEN;
  wire RESET_SLOW;

  wire CLK_FAST;
  wire CLK_FAST_GEN;
  wire RESET_FAST;

  CLOCK_HANDLER clock_handler(
    CLK_SLOW_GEN,
    RESET_SLOW,
    CLK_FAST_GEN,
    RESET_FAST
  );

  // wire PMT_CSL;
  // wire PMT_SDA;

  // assign PMT_SCL = scllines[0];
  // assign PMT_SDA = sdalines[0];
    
  // wire [1:0] scllines; 
  // wire [1:0] sdalines;
 

  // wire [95:0] DAC_CONTROL_CONFIG = 0;
  // wire [15:0] DAC_CURRENT_DATA;

  // wb_hv hvinterface (
  //     .clk_i(CLK_FAST_GEN),
  //     .rst_i(RESET_FAST),

  //   .DAC_CONTROL_CONFIG(DAC_CONTROL_CONFIG),
  //   .DAC_CURRENT_DATA(DAC_CURRENT_DATA),
   
  //   .SCLLINES(scllines),
  //   .SDALINES(sdalines)
  // );

  reg [1:0] I2CLINES = 0; 
  reg [15:0] I2CDATA12 = 0;
  reg [15:0] I2CDATA34 = 0;
  reg 	      SENDI2C = 0;

  wire [1:0] SCLLINES;
  wire [1:0] SDALINES;
  wire I2CENABLE = SENDI2C;

    I2C4BYTES i2cpmod(.CLK(CLK_FAST_GEN),
                     .ENABLE(I2CENABLE),
                     .I2CLINES(I2CLINES),
                     .I2CDATA12(I2CDATA12),
                     .I2CDATA34(I2CDATA34),
                     .SCLLINES(SCLLINES),
                     .SDALINES(SDALINES));
  reg [2:0] EEPROMCHOICE = 3;
  reg [11:0] THRESHOLD1 = 200;

  initial begin 
    SENDI2C <= 0;
    #100;
    I2CLINES <= 2;
    I2CDATA12 <= {8'b11000000,EEPROMCHOICE,5'b00000};
    I2CDATA34 <= {THRESHOLD1, 4'b0000};
    SENDI2C <= 0;
    #50;
    SENDI2C <= 1;
    #10000;
    SENDI2C <= 0;
  end

    


endmodule