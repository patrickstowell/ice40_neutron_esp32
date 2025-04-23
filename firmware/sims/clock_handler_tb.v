`define SYNTHESIS
`timescale 1ns / 1ps

module clock_handler_tb();

  initial
  begin
    $dumpfile("clock_handler_tb.vcd");
    $dumpvars(0,clock_handler_tb);
    # 1000 $finish;
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

endmodule