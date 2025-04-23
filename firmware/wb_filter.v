`ifndef WBFILTER_v
`define WBFILTER_v
`include "sdfilter.v"
`include "parameters.v"
module wb_filter (
               input clkf_i,
               input             rst_i,
               input             signal_i,
               output            trigger_o,
               input[15:0] gate0,
               input[15:0] gateN,
               input[7:0] stageN
);

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   //
   // FILTER
   //
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////

   // GATE0 - Width of first stage
   // GATEN - Width of 1-15 stages
   // STAGEN - Trigger out stage selection
   // sd - output values from each stage
   wire [15:0]               sd;

   // Main Filter Handler Module, processes upto 16 stages
   sdfilter filter_handler (
                            .clk(clkf_i),
                            .in(signal_i),
                            .out(sd),
                            .reset(rst_i),
                            .gate0(gate0),
                            .gaten(gateN)
                            );

  reg triggergen;
  always @(posedge clkf_i) begin
  if (!rst_i) triggergen <= sd[stageN];
  else triggergen <= 0;
  end

  SB_GB myglobal1( .USER_SIGNAL_TO_GLOBAL_BUFFER(triggergen),
                   .GLOBAL_BUFFER_OUTPUT(trigger_o) );

endmodule

`endif
