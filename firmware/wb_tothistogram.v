
// // Wishbone compatible I2C looper.
// // Periodically sends the threshold commands to i2C chips.
// // Address loop is hardcoded.
// `include "parameters.v"
// module wb_tothistogram (
//     // wishbone interface
//     input         clkf_i,
//     input         rst_i,
//     // buffer interface
//     input signal,
//     input [7:0]        ramreadaddr_i,
//     output reg [15:0]  histreaddata_o,
//     output reg [15:0]  totcountertotal_o,
//     input countreset_i,
//     input iswaiting,
//     input isreset,
//     input isfill
// );

//    ///////////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////////
//    //
//    // DELAYED TOT COUNTER DEFINITION
//    //
//    ///////////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////////
//    //
//    reg [7:0]  ramtotwraddr = 0;
//    reg [15:0] ramtotwrdata = 0;
//    reg [7:0]  ramtotrdaddr = 0;
//    wire [15:0] ramtotrddata;
//    reg         ramtoten   = 0;
//    ram totram(ramtotwrdata, ramtotwraddr, ramtoten, clkf_i, ramtotrdaddr, ramtotrddata, clkf_i);

//    reg [11:0]  ramwriteaddr = 0;
//    reg [11:0]  ramreadaddr = 0;
//    wire [7:0]  TOPADDR = ramwriteaddr[11:4];
//    wire [3:0]  SUBADDR = ramwriteaddr[3:0];
//    wire [7:0]  TOPADDR2 = ramreadaddr[11:4];
//    wire [3:0]  SUBADDR2 = ramreadaddr[3:0];

//    reg [15:0] TOTCOUNTERLOCAL = 0;
//    reg        TOTIN = 0;
//    reg        TOTOUT = 0;
//    reg [15:0] TOTCOUNTERCURR = 0;

//    always @(posedge clkf_i) begin
//       ramwriteaddr <= ramwriteaddr + 1;
//       ramreadaddr  <= ramwriteaddr - 4060;

//       ramtoten <= (SUBADDR == 7);

//       ramtotwrdata[ SUBADDR ] <= signal;

//       ramtotwraddr <= TOPADDR;
//       ramtotrdaddr <= TOPADDR2;

//       if (!rst_i) begin
//          TOTIN  <= ramtotwrdata[ SUBADDR ];
//          TOTOUT <= ramtotrddata[ SUBADDR2 ];
//          TOTCOUNTERCURR <= TOTCOUNTERCURR + TOTIN - TOTOUT;
//       end
//       else
//         begin
//            TOTCOUNTERCURR <= 0;
//            TOTIN <= 0;
//            TOTOUT <= 0;
//         end

//       if (isfill) TOTCOUNTERLOCAL <= TOTCOUNTERCURR;
//       else if (isreset) TOTCOUNTERLOCAL <= 0;

//      end // always @ (posedge clkf_i)

//    ///////////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////////
//    //
//    // HISTOGRAM
//    //
//    ///////////////////////////////////////////////////////////////////////////
//    ///////////////////////////////////////////////////////////////////////////

//    reg [11:0]   histaddr = 0;
//    reg          histfill = 0;
//    reg          histreset = 0;
//    reg [11:0]   histraddr = 0;
//    wire [15:0]  histdatao;
//    ramhistogram ramhist(clkf_i,histaddr,histfill,countreset_i,histdatao);

//    reg [15:0]  FILLCOUNTER = 0;

//    always @(posedge clkf_i) begin

//       histaddr <= TOTCOUNTERLOCAL;

//       if (isfill) begin
//          FILLCOUNTER <= FILLCOUNTER + 1;

//          case(FILLCOUNTER)
//            0: histaddr <= TOTCOUNTERLOCAL;
//            1: histaddr <= TOTCOUNTERLOCAL;
//            2: histaddr <= TOTCOUNTERLOCAL;
//            3: histaddr <= TOTCOUNTERLOCAL;
//            4: histaddr <= TOTCOUNTERLOCAL;
//            5: histaddr <= TOTCOUNTERLOCAL;
//            6: histaddr <= TOTCOUNTERLOCAL;
//            7: histaddr <= TOTCOUNTERLOCAL;
//            8: histfill <= 1;
//            9: histfill <= 1;
//            default: histfill <= 0;

//          endcase

//       end else begin
//          FILLCOUNTER <= 0;
//          histfill    <= 0;
//          histaddr    <= ramreadaddr_i;
//       end // else: !if(CMD == `STATE_FILL)

//    end // always @ (posedge clkf_i)

//    always @(posedge clkf_i) begin
//      histreaddata_o     <= histdatao;
//      totcountertotal_o <= TOTCOUNTERLOCAL;
//    end

// endmodule
