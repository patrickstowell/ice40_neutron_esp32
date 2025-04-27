module EDGE_TRIGGER_HANDLER (
    CLK,
    RESET,
    SIGNAL1,
    SIGNAL2,
    TRIGGER_OUT,
    read_mode,
    EDGE_TRIGGER_CONFIG
  );

input CLK;
input RESET;
input SIGNAL1;
input SIGNAL2;
output TRIGGER_OUT;
input read_mode;
    input [7:0] EDGE_TRIGGER_CONFIG;

/////////////////////////////////////////
// Local Clocked Registration of CONFIG
/////////////////////////////////////////

    always @(posedge CLK) begin
        AND_FLAG <= EDGE_TRIGGER_CONFIG[7];
        WINDOW <= EDGE_TRIGGER_CONFIG[6:0];
    end
    
    
reg [31:0] CH1_CDOWN = 0;
reg [31:0] CH2_CDOWN = 0;
reg [6:0] WINDOW = 200;
reg AND_FLAG = 0;

reg trigg_and = 0;
reg trigg_or = 0;
always @(posedge CLK) begin

    if ((SIGNAL1)) CH1_CDOWN <= WINDOW;
    else CH1_CDOWN <= CH1_CDOWN - (CH1_CDOWN > 0);

    if ((SIGNAL2)) CH2_CDOWN <= WINDOW;
    else CH2_CDOWN <= CH2_CDOWN - (CH2_CDOWN > 0);

    trigg_and <= (CH1_CDOWN > 0) & (CH2_CDOWN > 0);
    trigg_or <= (CH1_CDOWN > 0) | (CH2_CDOWN > 0);

end

wire TRIGGER_OUT = (!read_mode) & (AND_FLAG & trigg_and) | (!AND_FLAG & trigg_or);
    
endmodule
