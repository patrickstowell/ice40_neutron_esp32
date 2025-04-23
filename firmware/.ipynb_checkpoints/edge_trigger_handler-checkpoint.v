module EDGE_TRIGGER_HANDLER (
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

/////////////////////////////////////////
// Local Clocked Registration of CONFIG
/////////////////////////////////////////


    
reg [31:0] CH1_CDOWN;
reg [31:0] CH2_CDOWN;

reg [31:0] WINDOW = 15;

reg trigg = 0;
always @(posedge CLK) begin

  if (SIGNAL1) CH1_CDOWN <= WINDOW;
  else CH1_CDOWN <= CH2_CDOWN - (CH1_CDOWN > 0);

  if (SIGNAL2) CH2_CDOWN <= WINDOW;
  else CH2_CDOWN <= CH2_CDOWN - (CH2_CDOWN > 0);

  trigg <= (CH1_CDOWN > 0) & (CH2_CDOWN > 0);

end

wire TRIGGER_OUT = trigg;

endmodule
