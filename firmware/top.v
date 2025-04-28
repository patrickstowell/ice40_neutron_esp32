// `include "fastpll.v"
`include "parameters.v"

//`include "wb_filter.v"
module TOP (
  output GPIOMCX1,
  inout DISC_SDA,
  output DISC_SCL,
  inout PMT_SDA,
  output PMT_SCL,
  inout BOARD_SDA,
  input BOARD_SCL,              
  input EXTSPI_SDO,
  input EXTSPI_SS,
  input EXTSPI_SCK,
  output EXTSPI_SDI,
  output PMT_LDO_PIN,
  output AMP_LDO_PIN,    
  output ADDR8,
  output ADDR7,
  output ADDR6,
  output ADDR5,
  output ADDR4,
  output ADDR3,
  output ADDR2,
  output ADDR1,
  input DISCOUT1,
  input DISCOUT2,
  input CLKIN,
  input CLKFIN
);


  ///////////////////////////////////////////////////////////////////////////
  // GLOBALS
  ///////////////////////////////////////////////////////////////////////////
  assign AMP_LDO_PIN = 1;
  assign PMT_LDO_PIN = 1;
  assign ADDR8 = 1;
  assign ADDR7 = 0;
  assign ADDR6 = 1;
  assign ADDR5 = 0;
  assign ADDR4 = 1;
  assign ADDR3 = 0;
  assign ADDR2 = 1;
  assign ADDR1 = 1;
  assign EXTSPI_SDI = 1;

  wire [7:0] CONFIG_GLOBAL;
  // 0 - COUNTER RESETS
  // 1 - RAM READ MODE

  wire [7:0] CONTROL_BYTE;

  wire FORCE_TRIGGER_RESET = CONTROL_BYTE[4];
  wire SELF_TRIGGER_RESET = CONTROL_BYTE[3];
  wire LIMIT_TRIGGER = CONTROL_BYTE[2];
  wire SOFT_RESET = CONTROL_BYTE[1];
  wire READ_MODE_GEN = CONTROL_BYTE[0];
  

  wire READ_MODE;
  SB_GB BUFFERED_READ_MODE(.USER_SIGNAL_TO_GLOBAL_BUFFER(READ_MODE_GEN),
                           .GLOBAL_BUFFER_OUTPUT(READ_MODE) );


  ///////////////////////////////////////////////////////////////////////////
  // CLOCK DEFINITION
  ///////////////////////////////////////////////////////////////////////////
  wire CLK_SLOW;
  wire CLK_SLOW_GEN;
  wire RESET_SLOW;

  wire CLK_FAST;
  wire CLK_FAST_GEN;
  wire RESET_FAST;

  CLOCK_HANDLER clock_handler(
    CLK_SLOW_GEN,
    RESET_SLOW,
    CLK_FAST_GEN,
    RESET_FAST
  );

  reg [1:0] CLK_SLOW_HALF_GEN = 0;
  reg [7:0] CLK_SLOW_EIGHT_GEN = 0;

  always @(posedge CLK_SLOW) begin
    CLK_SLOW_HALF_GEN <= CLK_SLOW_HALF_GEN + 1;
    CLK_SLOW_EIGHT_GEN <= CLK_SLOW_EIGHT_GEN + 1;
  end

  reg [7:0] EIGHT_RESET = 255;
  wire RESET_I2C = (EIGHT_RESET > 0);
  always @(posedge CLK_SLOW_EIGHT_GEN[7]) begin
    EIGHT_RESET <= EIGHT_RESET - RESET_I2C;
  end

  //* BUFFER ASSIGNMENT *//
  SB_GB BUFFERED_CLK_FAST(.USER_SIGNAL_TO_GLOBAL_BUFFER(CLK_FAST_GEN),
                          .GLOBAL_BUFFER_OUTPUT(CLK_FAST) );

  SB_GB BUFFERED_CLK_SLOW(.USER_SIGNAL_TO_GLOBAL_BUFFER(CLK_SLOW_HALF_GEN[1]),
                          .GLOBAL_BUFFER_OUTPUT(CLK_SLOW) );
    wire CLK_SLOW_HALF_GEN_OUT = CLK_SLOW_HALF_GEN[1];

  ///////////////////////////////////////////////////////////////////////////
  // SIGNAL INPUT SELECTION
  ///////////////////////////////////////////////////////////////////////////
  wire [7:0] SIGNAL_INPUT_CONFIG;
  wire SIGNAL_LINE_1;
  wire SIGNAL_LINE_1_GEN;
  wire SIGNAL_LINE_2;
  wire SIGNAL_LINE_2_GEN;

  SIGNAL_INPUT signal_input(
    .CLK(CLK_FAST),
    .SIGNAL1(DISCOUT1),
    .SIGNAL2(DISCOUT2),
    .SIGNAL_LINE_1(SIGNAL_LINE_1),
    .SIGNAL_LINE_2(SIGNAL_LINE_2),
    .read_mode(READ_MODE),
    .mconfig(SIGNAL_INPUT_CONFIG)
  );
  
  // BUFFER ASSIGNMENT
  SB_GB BUFFERED_SIGNAL_LINE_1(.USER_SIGNAL_TO_GLOBAL_BUFFER(SIGNAL_LINE_1_GEN),
                          .GLOBAL_BUFFER_OUTPUT(SIGNAL_LINE_1) );

  SB_GB BUFFERED_SIGNAL_LINE_2(.USER_SIGNAL_TO_GLOBAL_BUFFER(SIGNAL_LINE_2_GEN),
                          .GLOBAL_BUFFER_OUTPUT(SIGNAL_LINE_2) );


  ///////////////////////////////////////////////////////////////////////////
  // EDGE COINCIDENCE TRIGGER
  ///////////////////////////////////////////////////////////////////////////
  wire EDGE_TRIGGER;
    reg [7:0] EDGE_TRIGGER_CONFIG;

  EDGE_TRIGGER_HANDLER edge_trigger_handler (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL1(SIGNAL_LINE_1),
    .SIGNAL2(SIGNAL_LINE_2),
    .TRIGGER_OUT(EDGE_TRIGGER),
    .read_mode(READ_MODE),
    .EDGE_TRIGGER_CONFIG(EDGE_TRIGGER_CONFIG)
  );

  ///////////////////////////////////////////////////////////////////////////
  // TOT CALCULATORS
  ///////////////////////////////////////////////////////////////////////////
  wire [15:0] TOT_SHORT;
  wire [12:0] TOT_WINDOW_SHORT;
  TOT_CALCULATOR tot_short_window (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL(SIGNAL_LINE_1 | SIGNAL_LINE_2),
    .TOTOUTPUT(TOT_SHORT),
    .WINDOW(TOT_WINDOW_SHORT)
  );

  wire [15:0] TOT_LONG;
  wire [12:0] TOT_WINDOW_LONG;
  TOT_CALCULATOR tot_long_window (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL(SIGNAL_LINE_1 | SIGNAL_LINE_2),
    .TOTOUTPUT(TOT_LONG),
    .WINDOW(TOT_WINDOW_LONG)
  );


  ///////////////////////////////////////////////////////////////////////////
  // TOT TRIGGER
  ///////////////////////////////////////////////////////////////////////////
  wire TOT_TRIGGER;
  wire [15:0] TOT_TRIGGER_CONFIG;
  TOT_TRIGGER_HANDLER tot_trigger_handler (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .TOT_SHORT(TOT_SHORT),
    .TOT_LONG(TOT_LONG),
    .TRIGGER_OUT(TOT_TRIGGER),
    .read_mode(READ_MODE),
    .mconfig(TOT_TRIGGER_CONFIG)
  );


  ///////////////////////////////////////////////////////////////////////////
  // STAGED FILTER TRIGGER
  ///////////////////////////////////////////////////////////////////////////
  wire FILTER_TRIGGER;
  wire [15:0] FILTER_TRIGGER_CONFIG;
  STAGED_FILTER_HANDLER staged_trigger_handler (
    .CLK(CLK_FAST),
    .RESET(RESET_FAST),
    .SIGNAL1(SIGNAL_LINE_1),
    .SIGNAL2(SIGNAL_LINE_2),
    .TRIGGER_OUT(FILTER_TRIGGER),
    .read_mode(READ_MODE),
    .mconfig(FILTER_TRIGGER_CONFIG)
  );


  ///////////////////////////////////////////////////////////////////////////
  // EXTERNAL TRIGGER
  ///////////////////////////////////////////////////////////////////////////
  wire EXTERNAL_TRIGGER = 0;
  // EXTERNAL_TRIGGER_HANDLER external_trigger_handler (
  //   .CLK(CLK_FAST),
  //   .RESET(RESET_FAST),
  //   .EXTSIG1(EXTSIG1),
  //   .EXTSIG2(EXTSIG2),
  //   .EXTSIG3(EXTSIG3),
  //   .EXTSIG4(EXTSIG4),
  //   .read_mode(READMODE),
  //   .mconfig(EXTERNAL_TRIGGER_CONFIG)
  // );


  ///////////////////////////////////////////////////////////////////////////
  // TRIGGER HANDLER MODULE [Handles choice, delay, and holdoff]
  ///////////////////////////////////////////////////////////////////////////
  wire FINAL_TRIGGER;
  wire [15:0] TRIGGER_HANDLER_CONFIG;
  wire LIVE_ACQUISITION;
  wire TRIGGER_ACTIVE;

  // COINCIDENCE LOGIC REQUIREMENT IS ALWAYS AND CHECK

  // Module requirements are that on a high of any trigger input
  // it will based on the selected trigger issue a delay for X clock ticks
  // then a holdoff for Y clock ticks. Any other modules hoping to 'stamp'
  // the pulse should look for the trigger active edge.
  
  // NEED OPTION FOR HARD RESET

  TRIGGER_HANDLER trigger_handler(
    .EDGE_TRIGGER(EDGE_TRIGGER),
    .TOT_TRIGGER(TOT_TRIGGER),
    .FILTER_TRIGGER(FILTER_TRIGGER),
    .EXTERNAL_TRIGGER(EXTERNAL_TRIGGER),
    .TRIGGER_OUT(TRIGGER_ACTIVE),
    .LIVE_ACQUISITION(LIVE_ACQUISITION),
    .read_mode(READ_MODE),
    .mconfig(TRIGGER_HANDLER_CONFIG)
  );


//   ///////////////////////////////////////////////////////////////////////////
//   // TRIGGER METRICS
//   ///////////////////////////////////////////////////////////////////////////
//   // Individual trigger metrics for N signals

//   // reg [47:0] LIVE_TIME = 0;
//   // reg [47:0] DEAD_TIME = 0;
//   // reg [47:0] NTRIGGERS = 0;
//   // reg [47:0] NSINGLES1 = 0;
//   // reg [47:0] NSINGLES2 = 0;

//   // reg [1:0] TRIG_BUFFER = 0;
//   // reg [1:0] CH1_SBUFFER = 0;
//   // reg [1:0] CH2_SBUFFER = 0;

//   // always @(posedge CLK_FAST) begin
//   //   LIVE_TIME <= LIVE_TIME + LIVE_ACQUISITION;
//   //   DEAD_TIME <= DEAD_TIME + DEAD_ACQUISITION;

//   //   TRIG_BUFFER <= {TRIG_BUFFER[0], LIVE_ACQUISITION};
//   //   CH1_SBUFFER <= {CH1_SBUFFER[0], SIGNAL_LINE_1};
//   //   CH2_SBUFFER <= {CH2_SBUFFER[0], SIGNAL_LINE_2};

//   //   NTRIGGERS <= NTRIGGERS + (!TRIG_BUFFER[0] & TRIG_BUFFER[1]);
//   //   NSINGLES1 <= NSINGLES1 + (!CH1_SBUFFER[0] & CH1_SBUFFER[1]);
//   //   NSINGLES2 <= NSINGLES2 + (!CH2_SBUFFER[0] & CH2_SBUFFER[1]);
//   // end


// //   ///////////////////////////////////////////////////////////////////////////
// //   // SAVE TO MEMORY BUFFERS
// //   ///////////////////////////////////////////////////////////////////////////

// //   // EVENT INDEX [1BRAM]
// //   // TIMESTAMP1 [1BRAM]
// //   // TIMESTAMP2 [1BRAM]
// //   // EVENT STAGE CODE [1BRAM]
// //   // EVENT PSD SHORT [1BRAM]
// //   // EVENT PSD LONG [1BRAM]




//   // reg [7:0]  ramtotwraddr = 0;
//   // reg [15:0] longramtotwrdata = 0;
//   // reg [15:0] shortramtotwrdata = 0;
//   // reg [15:0] eventbuframtotwrdata = 0;


//   // reg [7:0]  ramtotrdaddr = 0;
//   // wire [15:0] ramtotrddata;
//   // reg         ramtoten   = 0;
//   // ram event_buf(eventbuframtotwrdata, ramtotwraddr, ramtoten, CLK_FAST, ramtotrdaddr, ramtotrddata, CLK_FAST);
//   // ram longtot_ram(longramtotwrdata, ramtotwraddr, ramtoten, CLK_FAST, ramtotrdaddr, ramtotrddata, CLK_FAST);
//   // ram shorttot_ram(shortramtotwrdata, ramtotwraddr, ramtoten, CLK_FAST, ramtotrdaddr, ramtotrddata, CLK_FAST);

//   // wire TRIGGER_STROBE = (!TRIG_BUFFER[0] & TRIG_BUFFER[1]);

//   // always @(posedge CLK_FAST ) begin
//   //   if (TRIGGER_STROBE) begin
//   //     ramtotwraddr <= ramtotwraddr + 1;
//   //     longramtotwrdata <= TOT_LONG;
//   //     shortramtotwrdata <= TOT_SHORT;
//   //     eventbuframtotwrdata <= NTRIGGERS;
//   //   end
//   // end

//   // localparam WIDTH=16,     // fixed data width: 16-bits
//   //   localparam DEPTH=16384,  // fixed depth: 16K 
//   //   localparam ADDRW=$clog2(DEPTH)
//   //   ) (
//   //   input wire logic clk,
//   //   input wire logic [3:0] we,
//   //   input wire logic [ADDRW-1:0] addr,
//   //   input wire logic [WIDTH-1:0] data_in,
//   //   output     logic [WIDTH-1:0] data_out
//   //   );


//   //  SB_SPRAM256KA spram_inst (
//   //       .ADDRESS(spram_addr),
//   //       .DATAIN(spram_datain),
//   //       .MASKWREN(0xF),
//   //       .WREN(1),
//   //       .CHIPSELECT(1'b1),
//   //       .CLOCK(CLK_FAST),
//   //       .STANDBY(1'b0),
//   //       .SLEEP(1'b0),
//   //       .POWEROFF(1'b1),
//   //       .DATAOUT(spram_dataout)
//   //   );




 //////////////////////////////
 // DAC CONTROL MASTER
 //////////////////////////////
    // assign PMT_SCL = BOARD_SCL;
    // assign PMT_SDA = BOARD_SDA;

    assign PMT_SCL = scllines[1];
    assign PMT_SDA = sdalines[1];
    
    wire [1:0] scllines;
  //   = {
  //   DISC_SCL,
  //   PMT_SCL
  // };
    wire [1:0] sdalines;
    // = {
    // DISC_SDA,
    // PMT_SDA
  // };

  // assign sdalines[0] = 1;
  // assign sdalines[1] = 1;
    
  // assign scllines[0] = 1;
  // assign scllines[1] = 1;
    

  // wire DACEEPROM;
  // wire DACACTIVE;
  // wire [11:0] HVTARGET;
  // wire [11:0] HVLIMIT;
  // wire [7:0]  HVRAMPSPEED;

  // wire [11:0] THRESHOLD1;
  // wire [11:0] THRESHOLD2;

  wire [95:0] DAC_CONTROL_CONFIG;
  wire [15:0] DAC_CURRENT_DATA;

  wb_hv hvinterface (
      .clk_i(CLK_FAST),
      .rst_i(RESET_FAST),

    .DAC_CONTROL_CONFIG(DAC_CONTROL_CONFIG),
    .DAC_CURRENT_DATA(DAC_CURRENT_DATA),
   
    .SCLLINES(scllines),
    .SDALINES(sdalines)
  );



//   ///////////////////////////////////////////////////////////////////////////
//   // I2C COMMAND INTERFACE
//   ///////////////////////////////////////////////////////////////////////////
  i2c_control i2c_handler(
    .SCL(BOARD_SCL), 
    .SDA(BOARD_SDA),
    .RST(RESET_SLOW),
    .o_reg_SIGNAL_INPUT_CONFIG(SIGNAL_INPUT_CONFIG),
    .o_reg_EDGE_TRIGGER_CONFIG(EDGE_TRIGGER_CONFIG),
    .o_reg_TOT_WINDOW_SHORT(TOT_WINDOW_SHORT),
    .o_reg_TOT_WINDOW_LONG(TOT_WINDOW_LONG),
    .o_reg_TOT_TRIGGER_CONFIG(TOT_TRIGGER_CONFIG),
    .o_reg_FILTER_TRIGGER_CONFIG(FILTER_TRIGGER_CONFIG),
    .o_reg_TRIGGER_HANDLER_CONFIG(TRIGGER_HANDLER_CONFIG),

    .o_reg_DAC_CONTROL_CONFIG(DAC_CONTROL_CONFIG),
    .i_reg_DAC_CURRENT_DATA(DAC_CURRENT_DATA),
    .o_reg_CONTROL_BYTE(CONTROL_BYTE)
    

    // .i_reg_HVCURRENT( HVCURRENT )

    // .i_reg_ntrigger(BUFFER_NTRIGGER),
    // .i_reg_livetime(BUFFER_LIVETIME), 
    // .i_reg_deadtime(BUFFER_DEADTIME), 
    // .i_reg_delaytime(BUFFER_DELAYTIME),
    // .i_reg_holdofftime(BUFFER_HOLDOFF),
    // .i_reg_status(BUFFER_STATUS),

    // .o_reg_mconfig(BUFFER_CONFIG),
    // .o_reg_forcecmd(BUFFER_CONTROL)

  );


endmodule
