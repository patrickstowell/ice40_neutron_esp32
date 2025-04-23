`ifndef I2CSLAVE_v
`define I2CSLAVE_v

//////////////////////////////////////////////////////////////////////
////                                                              ////
//// i2cSlave.v                                                   ////
////                                                              ////
//// This file is part of the i2cSlave opencores effort.
//// <http://www.opencores.org/cores//>                           ////
////                                                              ////
//// Module Description:                                          ////
//// You will need to modify this file to implement your
//// interface.
////                                                              ////
//// To Do:                                                       ////
////
////                                                              ////
//// Author(s):                                                   ////
//// - Steve Fielding, sfielding@base2designs.com                 ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
////                                                              ////
//// Copyright (C) 2008 Steve Fielding and OPENCORES.ORG          ////
////                                                              ////
//// This source file may be used and distributed without         ////
//// restriction provided that this copyright statement is not    ////
//// removed from the file and that any derivative work contains  ////
//// the original copyright notice and the associated disclaimer. ////
////                                                              ////
//// This source file is free software; you can redistribute it   ////
//// and/or modify it under the terms of the GNU Lesser General   ////
//// Public License as published by the Free Software Foundation; ////
//// either version 2.1 of the License, or (at your option) any   ////
//// later version.                                               ////
////                                                              ////
//// This source is distributed in the hope that it will be       ////
//// useful, but WITHOUT ANY WARRANTY; without even the implied   ////
//// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR      ////
//// PURPOSE. See the GNU Lesser General Public License for more  ////
//// details.                                                     ////
////                                                              ////
//// You should have received a copy of the GNU Lesser General    ////
//// Public License along with this source; if not, download it   ////
//// from <http://www.opencores.org/lgpl.shtml>                   ////
////                                                              ////
//////////////////////////////////////////////////////////////////////
//
`include "i2cSlave_define.v"


module i2cSlave (
                 clk,
                 rst,
                 sda,
                 scl,
                 GATE0,
                 GATEN,
                 STAGEN,
                 RAMREADDATA,
                 RAMREADADDR,
                 RAMCHOICE,

                 NTRIGGER,
                 LIVETIME,
                 DEADTIME,
                 DELAYTIME,
                 HOLDOFFTIME,
                 STATUS,
                 CONFIG,
                 FORCECMD,
                 LOGGING,

                 HISTREADDATA,
                 TOTCOUNTERTOTAL,
                 HISTRESET,
                 ready,
                I2CACTIVE,
                HVTARGET,
                HVLIMIT,
                RAMPSPEED,
                THRESHOLD1,
                THRESHOLD2,
                EEPROMCHOICE
);

input clk;
input rst;
inout sda;
input scl;


output [15:0] GATE0;
output [15:0] GATEN;
output [7:0] STAGEN;
output [7:0] RAMREADADDR;
input [15:0] RAMREADDATA;
output [7:0] RAMCHOICE;

// input [3:0]      CMD;
input [15:0] NTRIGGER;
input [55:0] LIVETIME;
input [55:0] DEADTIME;
output [15:0] DELAYTIME;
output [15:0] HOLDOFFTIME;
input [7:0] STATUS;
output [7:0] CONFIG;
output [7:0] FORCECMD;
input [15:0] HISTREADDATA;
input [15:0] TOTCOUNTERTOTAL;
output HISTRESET;

output 			       I2CACTIVE;
output [11:0] 		    HVTARGET;
output [11:0] 		    HVLIMIT;
output [15:0]         RAMPSPEED;
output [11:0] 		    THRESHOLD1;
output [11:0] 		    THRESHOLD2;
output [2:0] 		    EEPROMCHOICE;



output   ready;
reg [1:0] startStopDetState;
wire clearStartStopDet;
wire sdaOut;
wire sdaIn;
wire [7:0] regAddr;
wire [7:0] dataToRegIF;
wire writeEn;
wire [7:0] dataFromRegIF;
reg [1:0] rstPipe;
wire rstSyncToClk;
reg startEdgeDet;
input [15:0] LOGGING;

registerInterface u_registerInterface(
                                      .clk(clk),
                                      .addr(regAddr),
                                      .dataIn(dataToRegIF),
                                      .writeEn(writeEn),
                                      .dataOut(dataFromRegIF),
                                      .GATE0(GATE0),
                                      .GATEN(GATEN),
                                      .STAGEN(STAGEN),
                                      .RAMREADDATA(RAMREADDATA),
                                      .RAMREADADDR(RAMREADADDR),
                                      .RAMCHOICE(RAMCHOICE),
                                      .NTRIGGER(NTRIGGER),
                                      .LIVETIME(LIVETIME),
                                      .DEADTIME(DEADTIME),
                                      .DELAYTIME(DELAYTIME),
                                      .HOLDOFFTIME(HOLDOFFTIME),
                                      .STATUS(STATUS),
                                      .CONFIG(CONFIG),
                                      .FORCECMD(FORCECMD),
                                      .HISTREADDATA(HISTREADDATA),
                                      .TOTCOUNTERTOTAL(TOTCOUNTERTOTAL),
                                      .HISTRESET(HISTRESET),
                                      .LOGGING(LOGGING),
                                      .I2CACTIVE(I2CACTIVE),
                                      .HVTARGET(HVTARGET),
                                      .HVLIMIT(HVLIMIT),
                                      .RAMPSPEED(RAMPSPEED),
                                      .THRESHOLD1(THRESHOLD1),
                                      .THRESHOLD2(THRESHOLD2),
                                      .EEPROMCHOICE(EEPROMCHOICE)
                                      );


// local wires and regs
   assign ready = 1;
 //(startStopDetState == `STOP_DET);

reg sdaDeb;
reg sclDeb;
reg [`DEB_I2C_LEN-1:0] sdaPipe;
reg [`DEB_I2C_LEN-1:0] sclPipe;

reg [`SCL_DEL_LEN-1:0] sclDelayed;
reg [`SDA_DEL_LEN-1:0] sdaDelayed;


   reg SDA_output_reg = 1;

//assign SDA = (SDA_output_reg) ? SDA_out : 'bz;
assign sda = (sdaOut == 1'b0) ? 1'b0 : 1'bz;
assign sdaIn = sda;

// sync rst rsing edge to clk
always @(posedge clk) begin
  if (rst == 1'b1)
    rstPipe <= 2'b11;
  else
    rstPipe <= {rstPipe[0], 1'b0};
end

assign rstSyncToClk = rstPipe[1];

// debounce sda and scl
always @(posedge clk) begin
  if (rstSyncToClk == 1'b1) begin
    sdaPipe <= {`DEB_I2C_LEN{1'b1}};
    sdaDeb <= 1'b1;
    sclPipe <= {`DEB_I2C_LEN{1'b1}};
    sclDeb <= 1'b1;
  end
  else begin
    sdaPipe <= {sdaPipe[`DEB_I2C_LEN-2:0], sdaIn};
    sclPipe <= {sclPipe[`DEB_I2C_LEN-2:0], scl};
    if (&sclPipe[`DEB_I2C_LEN-1:1] == 1'b1)
      sclDeb <= 1'b1;
    else if (|sclPipe[`DEB_I2C_LEN-1:1] == 1'b0)
      sclDeb <= 1'b0;
    if (&sdaPipe[`DEB_I2C_LEN-1:1] == 1'b1)
      sdaDeb <= 1'b1;
    else if (|sdaPipe[`DEB_I2C_LEN-1:1] == 1'b0)
      sdaDeb <= 1'b0;
  end
end


// delay scl and sda
// sclDelayed is used as a delayed sampling clock
// sdaDelayed is only used for start stop detection
// Because sda hold time from scl falling is 0nS
// sda must be delayed with respect to scl to avoid incorrect
// detection of start/stop at scl falling edge.
always @(posedge clk) begin
  if (rstSyncToClk == 1'b1) begin
    sclDelayed <= {`SCL_DEL_LEN{1'b1}};
    sdaDelayed <= {`SDA_DEL_LEN{1'b1}};
  end
  else begin
    sclDelayed <= {sclDelayed[`SCL_DEL_LEN-2:0], sclDeb};
    sdaDelayed <= {sdaDelayed[`SDA_DEL_LEN-2:0], sdaDeb};
  end
end

// start stop detection
always @(posedge clk) begin
  if (rstSyncToClk == 1'b1) begin
    startStopDetState <= `NULL_DET;
    startEdgeDet <= 1'b0;
  end
  else begin
    if (sclDeb == 1'b1 && sdaDelayed[`SDA_DEL_LEN-2] == 1'b0 && sdaDelayed[`SDA_DEL_LEN-1] == 1'b1)
      startEdgeDet <= 1'b1;
    else
      startEdgeDet <= 1'b0;
    if (clearStartStopDet == 1'b1)
      startStopDetState <= `NULL_DET;
    else if (sclDeb == 1'b1) begin
      if (sdaDelayed[`SDA_DEL_LEN-2] == 1'b1 && sdaDelayed[`SDA_DEL_LEN-1] == 1'b0)
        startStopDetState <= `STOP_DET;
      else if (sdaDelayed[`SDA_DEL_LEN-2] == 1'b0 && sdaDelayed[`SDA_DEL_LEN-1] == 1'b1)
        startStopDetState <= `START_DET;
    end
  end
end





serialInterface u_serialInterface (
  .clk(clk),
  .rst(rstSyncToClk | startEdgeDet),
  .dataIn(dataFromRegIF),
  .dataOut(dataToRegIF),
  .writeEn(writeEn),
  .regAddr(regAddr),
  .scl(sclDelayed[`SCL_DEL_LEN-1]),
  .sdaIn(sdaDeb),
  .sdaOut(sdaOut),
  .startStopDetState(startStopDetState),
  .clearStartStopDet(clearStartStopDet)
);


endmodule

`endif
