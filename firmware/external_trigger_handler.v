module EXTERNAL_TRIGGER_HANDLER (
    CLK,
    RESET,
    EXTSIG1,
    EXTSIG2,
    EXTSIG3,
    EXTSIG4,
    TRIGGER_OUT,
    read_mode,
    mconfig
  );

input CLK;
input RESET;
input EXTSIG1;
input EXTSIG2;
input EXTSIG3;
input EXTSIG4;
output TRIGGER_OUT;
input read_mode;
input [15:0] mconfig;

wire TRIGGER_OUT = 0;

endmodule