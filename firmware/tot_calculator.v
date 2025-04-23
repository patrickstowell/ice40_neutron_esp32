
module TOT_CALCULATOR(
    CLK,
    RESET,
    SIGNAL,
    TOTOUTPUT,
    WINDOW
    
);

input CLK;
input RESET;
input SIGNAL;
input [15:0] WINDOW;
output reg [15:0] TOTOUTPUT;

    // ROLLING RAM WINDOW
    // 

    // The BRAM in ICE40 is only 8 bits for address [256 slots], and then 16-bit data.
    // This means we can have 4096 possible bit to set, but we need to read/write it
    // in 16 bit chunks. We use a rolling counter that can go up to 4096, but then interpret
    // The top 8 bits as the main RAM address, and the bottom 4 bits as the address inside the 16-bit
    // word stored in the RAM.
    // This allows the BRAM to save a full 4096 bit trace corresponding to 20.96us length
    // when running at 200MHz.

    // Each RAM module has a read and write location that can be independent, so if we read at
    // once side, and write at the other we can create a configurable 4096 length delay line with
    // the ram.


   reg [7:0]  ramtotwraddr = 0;
   reg [15:0] ramtotwrdata = 0;
   reg [7:0]  ramtotrdaddr = 0;
   wire [15:0] ramtotrddata;
   reg         ramtoten   = 0;
//    ram totram(ramtotwrdata, ramtotwraddr, ramtoten, CLK, ramtotrdaddr, ramtotrddata, CLK);
   ram totram(ramtotwrdata, TOPADDR, ramtoten, CLK, TOPADDR2, ramtotrddata, CLK);


   reg [11:0]  ram_write_address = 0;
   reg [11:0]  ram_reads_address = 0;

   wire [7:0]  TOPADDR = ram_write_address[11:4];
   wire [3:0]  SUBADDR = ram_write_address[3:0];

   wire [7:0]  TOPADDR2 = ram_reads_address[11:4];
   wire [3:0]  SUBADDR2 = ram_reads_address[3:0];
   wire [3:0]  SUBADDR2_FLIP = 15-ram_reads_address[3:0];


   reg [15:0] TOTCOUNTERLOCAL = 0;
   reg        TOTIN = 0;
   reg        TOTOUT = 0;
   reg [15:0] TOTCOUNTERCURR = 0;

    reg [15:0] localbuffer = 0;
   always @(posedge CLK) begin

      ram_write_address <= ram_write_address + 1;
      ram_reads_address  <= ram_write_address + WINDOW;

      ramtoten <= 1;

      ramtotwrdata[SUBADDR] <= SIGNAL;
    //   if (ramtoten) 
        // ramtotwrdata <= localbuffer;

    //   ramtotwraddr <= TOPADDR;
    //   ramtotrdaddr <= TOPADDR2;

      if (!RESET) begin
         TOTIN  <= ramtotwrdata[ SUBADDR ];
         TOTOUT <= ramtotrddata[ SUBADDR2 ];
         TOTCOUNTERCURR <= TOTCOUNTERCURR + TOTIN - TOTOUT;
      end
      else
        begin
           TOTCOUNTERCURR <= 0;
           TOTIN <= 0;
           TOTOUT <= 0;
        end

      if (RESET) TOTOUTPUT <= 0;
      else TOTOUTPUT <= TOTCOUNTERCURR;

     end // always @ (posedge clkf_i)



endmodule