`ifndef SDFILTER_v
`define SDFILTER_v

module sdfilter (
	       input         clk,
	       input         in,
	       output [15:0] out,
               input         reset,
               input [15:0]  gate0,
               input [15:0]  gaten
                 );
   reg                      synced = 0;

   reg [15:0]               indelay_0 = 0;
   reg [15:0]               indelay_1 = 0;
   reg [15:0]               indelay_2 = 0;
   reg [15:0]               indelay_3 = 0;
   reg [15:0]               indelay_4 = 0;
   reg [15:0]               indelay_5 = 0;
   reg [15:0]               indelay_6 = 0;
   reg [15:0]               indelay_7 = 0;
   reg [15:0]               indelay_8 = 0;
   reg [15:0]               indelay_9 = 0;
   reg [15:0]               indelay_10 = 0;
   reg [15:0]               indelay_11 = 0;
   reg [15:0]               indelay_12 = 0;
   reg [15:0]               indelay_13 = 0;
   reg [15:0]               indelay_14 = 0;
   reg [15:0]               indelay_15 = 0;

   reg [1:0] edge_buffer = 0;

   genvar gi;
   always @(posedge clk) begin
     edge_buffer <= {edge_buffer[0], in};
     
	 if (!reset) begin
      synced <= !edge_buffer[1] && edge_buffer[0];
      indelay_0  <= {indelay_0[14:0], synced};
      indelay_1  <= {indelay_1[14:0],  |(indelay_0 & gate0) & synced};
      indelay_2  <= {indelay_2[14:0],  |(indelay_1 & gaten) & synced};
      indelay_3  <= {indelay_3[14:0],  |(indelay_2 & gaten) & synced};
      indelay_4  <= {indelay_4[14:0],  |(indelay_3 & gaten) & synced};
      indelay_5  <= {indelay_5[14:0],  |(indelay_4 & gaten) & synced};
      indelay_6  <= {indelay_6[14:0],  |(indelay_5 & gaten) & synced};
      indelay_7  <= {indelay_7[14:0],  |(indelay_6 & gaten) & synced};
      indelay_8  <= {indelay_8[14:0],  |(indelay_7 & gaten) & synced};
      indelay_9  <= {indelay_9[14:0],  |(indelay_8 & gaten) & synced};
      indelay_10 <= {indelay_10[14:0], |(indelay_9 & gaten) & synced};
      indelay_11 <= {indelay_11[14:0], |(indelay_10 & gaten) & synced};
      indelay_12 <= {indelay_12[14:0], |(indelay_11 & gaten) & synced};
      indelay_13 <= {indelay_13[14:0], |(indelay_12 & gaten) & synced};
      indelay_14 <= {indelay_14[14:0], |(indelay_13 & gaten) & synced};
      indelay_15 <= {indelay_15[14:0], |(indelay_14 & gaten) & synced};
	end else begin
		synced <= 0;
		indelay_0 <= 0;
		indelay_1 <= 1;
		indelay_2 <= 0;
		indelay_3 <= 0;
		indelay_4 <= 0;
		indelay_5 <= 0;
		indelay_6 <= 0;
		indelay_7 <= 0;
		indelay_8 <= 0;
		indelay_9 <= 0;
		indelay_10 <= 0;
		indelay_11 <= 0;
		indelay_12 <= 0;
		indelay_13 <= 0;
		indelay_14 <= 0;
		indelay_15 <= 0;
	end
   end

   assign out[0]  = indelay_0[0];
   assign out[1]  = indelay_1[0];
   assign out[2]  = indelay_2[0];
   assign out[3]  = indelay_3[0];
   assign out[4]  = indelay_4[0];
   assign out[5]  = indelay_5[0];
   assign out[6]  = indelay_6[0];
   assign out[7]  = indelay_7[0];
   assign out[8]  = indelay_8[0];
   assign out[9]  = indelay_9[0];
   assign out[10] = indelay_10[0];
   assign out[11] = indelay_11[0];
   assign out[12] = indelay_12[0];
   assign out[13] = indelay_13[0];
   assign out[14] = indelay_14[0];
   assign out[15] = indelay_14[0];

endmodule // filter

`endif
