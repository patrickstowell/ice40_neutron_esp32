// module trigger_data_logger (
//     input wire CLK_FAST,
//     input wire [15:0] TOT_LONG,
//     input wire [15:0] TOT_SHORT,
//     input wire [47:0] LIVETIME,
//     input wire [15:0] NTRIGGERS,
//     input wire [1:0] TRIG_BUFFER,       // [1]=current, [0]=previous
//     input wire READ_MODE,
//     input wire SOFT_RESET,
//     input wire [13:0] ext_read_addr,    // External address when reading

//     output wire [15:0] spram_dataout
// );

//     // SPRAM parameters
//     localparam DEPTH = 16384;
//     localparam ADDRW = 14;

//     // SPRAM signals
//     reg [ADDRW-1:0] spram_addr = 0;
//     reg [15:0] spram_datain = 16'd0;
//     wire [15:0] spram_dataout;
//     reg [3:0] spram_maskwren = 4'hF;
//     reg spram_wren = 1'b0;

//     // FSM states
//     typedef enum logic [2:0] {
//         IDLE,
//         WRITE_EVENTID,
//         WRITE_TOTLONG,
//         WRITE_TOTSHORT,
//         WRITE_TIME0,
//         WRITE_TIME1,
//         WRITE_TIME2,
//         DONE,
//         RESETTING
//     } state_t;

//     state_t state = IDLE;
//     reg [ADDRW-1:0] write_addr = 0;
//     reg [ADDRW-1:0] reset_addr = 0;

//     // Trigger strobe generation
//     wire TRIGGER_STROBE = (!TRIG_BUFFER[0] & TRIG_BUFFER[1]);

//     always @(posedge CLK_FAST) begin
//         spram_wren <= 1'b0;  // default: no write

//         // Handle soft reset (clear all memory)
//         if (SOFT_RESET) begin
//             state <= RESETTING;
//             spram_addr <= reset_addr;
//             spram_datain <= 16'd0;
//             spram_wren <= 1'b1;

//             if (reset_addr < DEPTH - 1)
//                 reset_addr <= reset_addr + 1;
//             else begin
//                 reset_addr <= 0;
//                 write_addr <= 0;
//                 state <= IDLE;
//             end
//         end else if (READ_MODE) begin
//             // External read mode
//             spram_addr <= ext_read_addr;
//             spram_wren <= 1'b0;
//             state <= IDLE;  // freeze FSM
//         end else begin
//             // Normal write FSM
//             case (state)
//                 IDLE: begin
//                     if (TRIGGER_STROBE)
//                         state <= WRITE_EVENTID;
//                 end

//                 WRITE_EVENTID: begin
//                     spram_datain <= NTRIGGERS;
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= WRITE_TOTLONG;
//                 end

//                 WRITE_TOTLONG: begin
//                     spram_datain <= TOT_LONG;
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= WRITE_TOTSHORT;
//                 end

//                 WRITE_TOTSHORT: begin
//                     spram_datain <= TOT_SHORT;
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= WRITE_TIME0;
//                 end

//                 WRITE_TIME0: begin
//                     spram_datain <= LIVETIME[15:0];
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= WRITE_TIME1;
//                 end

//                 WRITE_TIME1: begin
//                     spram_datain <= LIVETIME[31:16];
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= WRITE_TIME2;
//                 end

//                 WRITE_TIME2: begin
//                     spram_datain <= LIVETIME[47:32];
//                     spram_addr <= write_addr;
//                     spram_wren <= 1'b1;
//                     write_addr <= write_addr + 1;
//                     state <= DONE;
//                 end

//                 DONE: begin
//                     state <= IDLE;
//                 end

//                 default: state <= IDLE;
//             endcase
//         end
//     end

//     // SPRAM instance
//     SB_SPRAM256KA spram_inst (
//         .ADDRESS(spram_addr),
//         .DATAIN(spram_datain),
//         .MASKWREN(spram_maskwren),
//         .WREN(spram_wren),
//         .CHIPSELECT(1'b1),
//         .CLOCK(CLK_FAST),
//         .STANDBY(1'b0),
//         .SLEEP(1'b0),
//         .POWEROFF(1'b1),
//         .DATAOUT(spram_dataout)
//     );

// endmodule
