`define SYNTHESIS
`timescale 1ns / 1ps

module trigger_combination_tb();

  initial
  begin
    $dumpfile("sims/trigger_combination_tb.vcd");
    $dumpvars(0,trigger_combination_tb);
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

  reg DISCOUT1;
  reg DISCOUT2;
  reg [2:0] SIGS;
  reg [7:0] SIGNAL_INPUT_CONFIG;
  // wire SIGNAL_LINE_1;
  wire SIGNAL_LINE_1_GEN;
  // wire SIGNAL_LINE_2;
  wire SIGNAL_LINE_2_GEN;


  SIGNAL_INPUT signal_input(
    .CLK(CLK_FAST),
    .SIGNAL1(DISCOUT1),
    .SIGNAL2(DISCOUT2),
    .SIGNAL_LINE_1(SIGNAL_LINE_1_GEN),
    .SIGNAL_LINE_2(SIGNAL_LINE_2_GEN),
    .read_mode(READ_MODE),
    .mconfig(SIGNAL_INPUT_CONFIG)
  );

  wire SIGNAL_LINE_1 = SIGNAL_LINE_1_GEN;
  wire SIGNAL_LINE_2 = SIGNAL_LINE_2_GEN;

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

  reg [15:0] STAGED_FILTER_CONFIG = 0;

  wire FILTER_TRIGGER;
  STAGED_FILTER_HANDLER staged_trigger_handler (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL1(SIGNAL_LINE_1),
    .SIGNAL2(SIGNAL_LINE_2),
    .TRIGGER_OUT(FILTER_TRIGGER),
    .read_mode(READ_MODE),
    .mconfig(STAGED_FILTER_CONFIG)
  );


  wire FINAL_TRIGGER;
  reg [15:0] TRIGGER_HANDLER_CONFIG;

  wire EDGE_TRIGGER = 0;
  wire EXTERNAL_TRIGGER = 0;

  TRIGGER_HANDLER trigger_handler(
    .CLK(CLK_FAST),
    .EDGE_TRIGGER(EDGE_TRIGGER),
    .TOT_TRIGGER(TOT_TRIGGER),
    .FILTER_TRIGGER(FILTER_TRIGGER),
    .EXTERNAL_TRIGGER(EXTERNAL_TRIGGER),
    .TRIGGER_OUT(FINAL_TRIGGER),
    // .read_mode(READ_MODE),
    .mconfig(TRIGGER_HANDLER_CONFIG)
  );




initial begin

  TRIGGER_HANDLER_CONFIG = 0;
  
  // ENABLE PULSER
  SIGNAL_INPUT_CONFIG[0] = 1;
  SIGNAL_INPUT_CONFIG[1] = 1;
  SIGNAL_INPUT_CONFIG[2] = 0;
  SIGNAL_INPUT_CONFIG[3] = 0;
  SIGNAL_INPUT_CONFIG[4] = 0;
  SIGNAL_INPUT_CONFIG[5] = 0;
  SIGNAL_INPUT_CONFIG[6] = 1;
  SIGNAL_INPUT_CONFIG[7] = 1;

end


initial begin

  STAGED_FILTER_CONFIG[7:0] <= 255;
  STAGED_FILTER_CONFIG[15:8] <= 65535;

end

endmodule