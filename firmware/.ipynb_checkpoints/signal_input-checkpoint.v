module SIGNAL_INPUT(
    CLK,
    SIGNAL1,
    SIGNAL2,
    read_mode,
    mconfig,
    SIGNAL_LINE_1,
    SIGNAL_LINE_2
);

input CLK;
input SIGNAL1;
input SIGNAL2;
input read_mode;
input [7:0] mconfig;
output SIGNAL_LINE_1;
output SIGNAL_LINE_2;

/////////////////////////////////////////
// Local Clocked Registration of CONFIG
/////////////////////////////////////////

// Configuration bits
reg enable_ch1 = 0; // - 0 enable 1
reg enable_ch2 = 0; // - 1 enable 2
reg invertlogic_ch1 = 0; // - 2 invert logic 1
reg invertlogic_ch2 = 0; // - 3 invert logic 2
reg edgeonly_ch1 = 0; // - 4 edge only
reg edgeonly_ch2 = 0; // - 5 edge only
reg pulser_ch1 = 0; // - 6 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
reg pulser_ch2 = 0; // - 7 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]

always @(posedge CLK) begin

    enable_ch1 <= mconfig[0];
    enable_ch2 <= mconfig[1];
    invertlogic_ch1 <= mconfig[2];
    invertlogic_ch2 <= mconfig[3];
    edgeonly_ch1 <= mconfig[4];
    edgeonly_ch2 <= mconfig[5];
    pulser_ch1 <= mconfig[6];
    pulser_ch2 <= mconfig[7];

end


/////////////////////////////////////////
// Channel Enable and Inverstion
/////////////////////////////////////////
reg [1:0] signals_in = 0;

always @(posedge CLK) begin
    signals_in[0] <= enable_ch1 & ( (invertlogic_ch1 & !SIGNAL1) | (!invertlogic_ch1 & SIGNAL1) );
    signals_in[1] <= enable_ch2 & ( (invertlogic_ch2 & !SIGNAL2) | (!invertlogic_ch2 & SIGNAL2) );
end


/////////////////////////////////////////
// Edge Based Filtering
/////////////////////////////////////////
reg [1:0] buffer_ch1 = 0;
reg [1:0] buffer_ch2 = 0;
reg [1:0] signals_out = 0;

always @(posedge CLK) begin
    buffer_ch1 <= {buffer_ch1[0], signals_in[0]};
    buffer_ch2 <= {buffer_ch2[0], signals_in[1]};

    signals_out[0] <= (edgeonly_ch1 & (!buffer_ch1[1] & buffer_ch1[0])) | (!edgeonly_ch1 & signals_in[0]);
    signals_out[1] <= (edgeonly_ch2 & (!buffer_ch2[1] & buffer_ch2[0])) | (!edgeonly_ch2 & signals_in[1]);    
end


// SIPM NOISE

    

    // 255-bit Galois LFSR register
    reg [254:0] lfsr = 255'h1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF;

    // Tap positions for x^255 + x^7 + 1 (primitive for 255-bit Galois LFSR)
    wire feedback = lfsr[254];

    // THRESHOLD: dynamically calculate based on clock and noise rate
    localparam integer THRESHOLD = (2**16 * 40_000_000) / 200_000_000;

    // Use upper 16 bits of LFSR for threshold comparison
    wire [15:0] lfsr_top = lfsr[254 -: 16];
    reg sipm_noise;
    integer i;

    always @(posedge CLK) begin

            // Update LFSR with Galois feedback
            for (i = 0; i < 255; i = i + 1) begin
                if (i == 0)
                    lfsr[i] <= lfsr[254] ^ lfsr[6];
                else
                    lfsr[i] <= lfsr[i-1];
            end

            // Generate pulse based on threshold
            if (lfsr_top < THRESHOLD)
                sipm_noise <= 1;
            else
                sipm_noise <= 0;
    end





/////////////////////////////////////////
// PULSER BASED PROCESSING
/////////////////////////////////////////
reg [15:0] pulse_buffer = 0;
reg pulser_out = 0;

reg [31:0] pulse_pattern = 32'b00100100001001010110010101111100;
always @(posedge CLK) begin
    pulse_buffer <= pulse_buffer + (pulser_ch1 | pulser_ch2);
    if (pulse_buffer < 32) pulser_out <= pulse_pattern[pulse_buffer] | sipm_noise;
    else pulser_out <= sipm_noise;
end


/////////////////////////////////////////
// OUTPUT COMBINATION
/////////////////////////////////////////
wire SIGNAL_LINE_LOCAL_1 = (!pulser_ch1 & signals_out[0]) | (pulser_ch1 & pulser_out);
wire SIGNAL_LINE_LOCAL_2 = (!pulser_ch2 & signals_out[1]) | (pulser_ch2 & pulser_out);

SB_GB BUFFERED_SIGNAL_LINE_1(
    .USER_SIGNAL_TO_GLOBAL_BUFFER(SIGNAL_LINE_LOCAL_1),
    .GLOBAL_BUFFER_OUTPUT(SIGNAL_LINE_1) 
);

SB_GB BUFFERED_SIGNAL_LINE_2(
    .USER_SIGNAL_TO_GLOBAL_BUFFER(SIGNAL_LINE_LOCAL_2),
    .GLOBAL_BUFFER_OUTPUT(SIGNAL_LINE_2) 
);


endmodule