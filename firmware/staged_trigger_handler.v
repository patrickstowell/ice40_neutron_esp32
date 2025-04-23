module STAGED_FILTER_HANDLER (
    CLK,
    RESET,
    SIGNAL1,
    SIGNAL2,
    TRIGGER_OUT,
    read_mode,
    mconfig
  );

input CLK;
input RESET;
input SIGNAL1;
input SIGNAL2;
output TRIGGER_OUT;
input read_mode;
input [15:0] mconfig;

wire [15:0] filters;
sdfilter sd (
  .clk(CLK),
  .in(SIGNAL1 | SIGNAL2),
  .reset(RESET),
  .out(filters),
  .gate0(mconfig[7:0]),
  .gaten(mconfig[15:0])
);


reg [15:0] countdown = 0;
always @(posedge CLK) begin
  if (TRIGGER_OUT) countdown <= 1000;
  else countdown <= countdown - (countdown > 0);
end

wire TRIGGER_OUT = filters[8] & !countdown;

endmodule