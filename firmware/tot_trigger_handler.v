module TOT_TRIGGER_HANDLER (
    CLK,
    RESET,
    TOT_SHORT,
    TOT_LONG,
    TRIGGER_OUT,
    read_mode,
    mconfig
  );

input CLK;
input RESET;
input [15:0] TOT_SHORT;
input [15:0] TOT_LONG;
output TRIGGER_OUT;
input read_mode;
input [15:0] mconfig;

wire TOT_THRESHOLD_CHECK = TOT_LONG > 100;
wire TOT_PSD_CHECK = (TOT_LONG*128/TOT_SHORT) > 2*128;

wire TRIGGER_BUFFER_IN = TOT_THRESHOLD_CHECK;
reg [1:0] EDGE_BUFFER = 0;
always @(posedge CLK) begin
  EDGE_BUFFER <= {EDGE_BUFFER[0], TRIGGER_BUFFER_IN};
end

wire TRIGGER_OUT = !EDGE_BUFFER[1] && EDGE_BUFFER[0];

endmodule