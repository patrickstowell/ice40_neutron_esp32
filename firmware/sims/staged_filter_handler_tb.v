`define SYNTHESIS
`timescale 1ns / 1ps

module staged_filter_handler_tb();

  initial
  begin
    $dumpfile("sims/staged_filter_handler_tb.vcd");
    $dumpvars(0,staged_filter_handler_tb);
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

initial begin
  
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