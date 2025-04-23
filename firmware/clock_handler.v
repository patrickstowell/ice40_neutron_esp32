module CLOCK_HANDLER (
	CLK_SLOW,
    RESET_SLOW,
    CLK_FAST,
    RESET_FAST
);

// PORTS
output CLK_SLOW;
output RESET_SLOW;
output CLK_FAST;
output RESET_FAST;


// `define SYNTHESIS
// `ifdef SYNTHESIS

// reg CLK_SLOW_V = 0;
// reg CLK_FAST_V = 0;

// always begin
//    #5 CLK_FAST_V  = ~CLK_FAST_V;
// end

// always begin
//    #20 CLK_SLOW_V = ~CLK_SLOW_V;
// end

// wire CLK_FAST = CLK_FAST_V;
// wire CLK_SLOW = CLK_SLOW_V;

// `else



///////////////////////////////////////
// 48 MHZ Oscillator DEFINITION (this is our slow)
///////////////////////////////////////
reg            CLK_SLOW_EN = 1;
reg            CLK_SLOW_POWERUP = 1;


SB_HFOSC OSCInst0 (
    .CLKHFEN(CLK_SLOW_EN),
    .CLKHFPU(CLK_SLOW_POWERUP),
    .CLKHF(CLK_SLOW)
)
/* synthesis ROUTE_THROUGH_FABRIC=0 */;
defparam OSCInst0.CLKHF_DIV = "0b00";


///////////////////////////////////////
// PLL GENERATED 250 MHZ CLOCK
///////////////////////////////////////
wire CLK_FAST_LOCKED;

pll_200M PLLModule(
    CLK_SLOW,
    CLK_FAST,
    CLK_FAST_LOCKED
);

// `endif

///////////////////////////////////////
// SLOW RESET
///////////////////////////////////////
reg [7:0] slow_reset_counter = 0;

always @(posedge CLK_SLOW) begin
    if (slow_reset_counter < 255)
        slow_reset_counter <= slow_reset_counter + 1;
end

wire RESET_SLOW = !slow_reset_counter[7];

///////////////////////////////////////
// FAST RESET
///////////////////////////////////////
reg [7:0] fast_reset_counter = 0;

always @(posedge CLK_FAST) begin
    if (fast_reset_counter < 255)
        fast_reset_counter <= fast_reset_counter + 1;    
end

wire RESET_FAST = !fast_reset_counter[7];


endmodule