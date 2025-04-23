`define SYNTHESIS
`timescale 1ns / 1ns

module tot_calculator_tb();

  initial
  begin
    $dumpfile("sims/tot_calculator_tb.vcd");
    $dumpvars(0,tot_calculator_tb);
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
  

  // TOT CALCULATOR (100NS WINDOW) [Uses 1BRAM]
  wire [15:0] TOT_SHORT;
  reg SIGNAL = 0;
  reg [15:0] window_short = 20;
  TOT_CALCULATOR tot_short_window (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL(SIGNAL),
    .TOTOUTPUT(TOT_SHORT),
    .WINDOW(window_short)
  );

  wire [15:0] TOT_LONG;
  reg [15:0] window_long = 50;
  TOT_CALCULATOR tot_long_window (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL(SIGNAL),
    .TOTOUTPUT(TOT_LONG),
    .WINDOW(window_long)
  );

  wire TOT_TRIGGER;
  TOT_TRIGGER_HANDLER tot_trigger_handler (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .TOT_SHORT(TOT_SHORT),
    .TOT_LONG(TOT_LONG),
    .TRIGGER_OUT(TOT_TRIGGER),
    .read_mode(READ_MODE),
    .mconfig()
  );




initial begin
  SIGNAL = 0;
  #100
  SIGNAL = 1;
  #1
  SIGNAL = 0;
  #100


  SIGNAL = 0;
  #100
  SIGNAL = 1;
  #2
  SIGNAL = 0;
  #100


  SIGNAL = 0;
  #100
  SIGNAL = 1;
  #10
  SIGNAL = 0;



  SIGNAL = 0;
  #100
  SIGNAL = 1;
  #1
  SIGNAL = 0;








end

endmodule