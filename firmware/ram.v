module ram (din, addr, write_en, clk, raddr, dout, clks);

   // 128x32 RAM, taken directly from Lattice ice40 memory programming guide
   parameter addr_width = 8;
   parameter data_width = 16;

   input [addr_width-1:0]  addr;
   input [data_width-1:0]  din;
   input                   write_en;
   input                   clk;
   input [addr_width-1:0]  raddr;

   output [data_width-1:0] dout;

   wire [data_width-1:0]   dout; // Register for output.
   reg [data_width-1:0]    mem [(1<<addr_width)-1:0];
   input                   clks;

   SB_RAM40_4K #(
		 .WRITE_MODE(0),
		 .READ_MODE(0)
   ) ram40_4k_256x16 (
		      .RDATA(dout[15:0]),
		      .RADDR({3'b0,raddr[7:0]}),
		      .RCLK(clks),
		      .RCLKE(1'b1),
		      .RE(1'b1),
                      .WADDR({3'b0,addr[7:0]}),
		      .WCLK(clk),
		      .WCLKE(1'b1),
		      .WDATA(din[15:0]),
		      .WE(write_en)		   ,
		      .MASK(16'b0)
                      );

endmodule
