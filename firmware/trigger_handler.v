module TRIGGER_HANDLER(
    CLK,
    EDGE_TRIGGER,
    TOT_TRIGGER,
    FILTER_TRIGGER,
    EXTERNAL_TRIGGER,
    TRIGGER_OUT,
    LIVE_ACQUISITION,
    read_mode,
    mconfig
);

input CLK;
input EDGE_TRIGGER;
input TOT_TRIGGER;
input FILTER_TRIGGER;
input EXTERNAL_TRIGGER;
output TRIGGER_OUT;
output LIVE_ACQUISITION;
input read_mode;
input [7:0] mconfig;

reg [4:0] trigger_state = 0;
reg trigger_issued = 0;
reg delay_issued = 0;
reg holdoff_issued = 0;

reg combined_trigger;

reg or_trigger;

always @(posedge CLK) begin
    or_trigger <= EDGE_TRIGGER | TOT_TRIGGER | FILTER_TRIGGER | EXTERNAL_TRIGGER;
end

reg [15:0] delay_counter = 1000;
reg [15:0] holdoff_counter = 1000;

always @(posedge CLK) begin

    if (or_trigger & trigger_state == 0) begin
        trigger_state <= 1;
    end

    if (trigger_state == 1) begin
        delay_counter <= delay_counter - (delay_counter > 0);
        if (delay_counter == 0) begin
            delay_counter <= 1000;
            trigger_state <= 2;
        end
    end

    if (trigger_state == 2) begin
        holdoff_counter <= holdoff_counter - (holdoff_counter > 0);
        if (holdoff_counter == 0) begin
            holdoff_counter <= 10000;
            trigger_state <= 0;
        end
    end 
end

// Create rising edge when moving from delay to holdoff
wire TRIGGER_OUT = (trigger_state == 2);
wire LIVE_ACQUISITION = (trigger_state == 0);

endmodule