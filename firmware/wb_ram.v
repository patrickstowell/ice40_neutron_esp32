
// Wishbone compatible I2C looper.
// Periodically sends the threshold commands to i2C chips.
// Address loop is hardcoded.
`include "parameters.v"
module wb_ram (
    // wishbone interface
    input         clkf_i,
    input         rst_i,

    input  signal_i,
    input [7:0]   ramreadaddr_i,
    output reg [15:0]  ramreaddata_o,
    input iswaiting,
    input isreset
);

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   //
   // RAM DEFINITION
   //
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   reg [7:0]   ramch0wraddr = 0;
   reg [15:0]  ramch0wrdata = 0;
   reg [7:0]   ramch0rdaddr = 0;
   wire [15:0] ramch0rddata;
   reg         ramch0en   = 0;
   ram ch0ram(ramch0wrdata, ramch0wraddr, ramch0en, clkf_i, ramch0rdaddr, ramch0rddata, clkf_i);

   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   //
   // RAM IO
   //
   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   reg [11:0] ramwriteaddr = 0;
   wire        iterateram = iswaiting || isreset;

   reg [11:0] ramwriteaddr_slow;
   reg [11:0] ramwriteaddr_slow2;

   always @(posedge clkf_i) begin
     ramch0rdaddr <= ramwriteaddr[11:4] - ramreadaddr_i;
     ramreaddata_o <= ramch0rddata;
   end

   always @(posedge clkf_i) begin

      ramwriteaddr <= ramwriteaddr + iterateram;

      ramch0en <= iterateram;
      ramch0wraddr <= ramwriteaddr[11:4];

      if (iswaiting) ramch0wrdata[ ramwriteaddr[3:0] ] <= signal_i;
      else ramch0wrdata[ ramwriteaddr[3:0] ] <= 0;
   end


endmodule
