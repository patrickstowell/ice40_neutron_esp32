#ifndef FPGA_PIN_DEF_h
#define FPGA_PIN_DEF_h

#define FPGA_PIN_EXTSPI_SS 2
#define FPGA_PIN_EXTSPI_SDI 3
#define FPGA_PIN_EXTSPI_SCK 4
#define FPGA_PIN_RGB2 41
#define FPGA_PIN_RGB1 40
#define FPGA_PIN_RGB0 39
#define FPGA_PIN_AMP_LDO_PIN 42
#define FPGA_PIN_BOARD_SCL 38
#define FPGA_PIN_DISCOUT1 43  # DISCOUT
#define FPGA_PIN_PMT_LDO_PIN 36
#define FPGA_PIN_35 35 # EMPTY PAD
#define FPGA_PIN_BOARD_SDA 37
#define FPGA_PIN_PMT_SDA 32
#define FPGA_PIN_PMT_SCL 34
#define FPGA_PIN_CLKIN 31
#define FPGA_PIN_ADDR8 28
#define FPGA_PIN_ADDR6 26
#define FPGA_PIN_ADDR7 27
#define FPGA_PIN_ADDR4 23
#define FPGA_PIN_ADDR5 25
#define FPGA_PIN_18 18 #EMPTY PAD
#define FPGA_PIN_ADDR1 19
#define FPGA_PIN_ADDR2 20
#define FPGA_PIN_CLKFIN 13 #EMPTY PAD
#define FPGA_PIN_ADDR3 21
#define FPGA_PIN_12 12 #EMPTY PAD
#define FPGA_PIN_11 11 #EMPTY PAD
#define FPGA_PIN_10 10 #EMPTY PAD
#define FPGA_PIN_ 9 9 #EMPTY PAD
#define FPGA_PIN_GPIOMCX2 6
#define FPGA_PIN_DISC_SCL 45
#define FPGA_PIN_EXTSPI_SDO 48
#define FPGA_PIN_DISC_SDA 44
#define FPGA_PIN_GPIOMCX1 47
#define FPGA_PIN_DISCOUT2 46

#endif
#ifndef PARAMS_v
#define PARAMS_v

// #define WB_SLAVE_FILTER_ADDR 0x02
// #define FILTER_GATE0_WR 0x01
// #define FILTER_GATEN_WR 0x02
// #define FILTER_NSTAGE_WR 0x03

// #define WB_SLAVE_FILTER_ADDR 8'b00000010
// #define WB_SLAVE_RAM0_ADDR   8'b00010000
// #define WB_SLAVE_RAM1_ADDR   8'b00010001
// #define WB_SLAVE_RAM2_ADDR   8'b00010010
// #define WB_SLAVE_RAM3_ADDR   8'b00010011
// #define WB_SLAVE_RAM4_ADDR   8'b00010100
// #define WB_SLAVE_RAM5_ADDR   8'b00010101
// #define WB_SLAVE_RAM6_ADDR   8'b00010110
// #define WB_SLAVE_RAM7_ADDR   8'b00010111

// #define STATE_FREE      8'b00000000 //0 //4'b0000
// #define STATE_IDLE      8'b00000001 //4'b0001
// #define	STATE_RESET     8'b00000010 //2 //4'b0010
// #define STATE_WAITING   8'b00000100 //3 //4'b0011
// #define STATE_COUNT     8'b00001000 //5 //4'b0101
// #define STATE_FILL      8'b00010000 //6 //4'b0110
// #define STATE_HOLDOFF   8'b00100000 //4 //4'b0100
// #define STATE_TRIGGERED 8'b01000000 //7 //4'b0111

// #define FSTATE_FREE      8'b10000000 //0 //4'b0000
// #define FSTATE_IDLE      8'b10000001 //4'b0001
// #define	FSTATE_RESET     8'b10000010 //2 //4'b0010
// #define FSTATE_WAITING   8'b10000100 //3 //4'b0011
// #define FSTATE_COUNT     8'b10001000 //5 //4'b0101
// #define FSTATE_FILL      8'b10010000 //6 //4'b0110
// #define FSTATE_HOLDOFF   8'b10100000 //4 //4'b0100
// #define FSTATE_TRIGGERED 8'b11000000 //7 //4'b0111

// #define WB_SLAVE_BUFFER_ADDR        8'b00000001
// #define BUFFER_FORCE_FREE_CMD       100
// #define BUFFER_FORCE_IDLE_CMD       101
// #define BUFFER_FORCE_RESET_CMD      102
// #define BUFFER_FORCE_WAITING_CMD    103
// #define	BUFFER_FORCE_HOLDOFF_CMD    104
// #define BUFFER_FORCE_COUNT_CMD      105
// #define BUFFER_FORCE_FILL_CMD       106
// #define	BUFFER_FORCE_TRIGGERED_CMD  107

// #define BUFFER_NTRIGGERS_RESET_RDWR 1
// #define BUFFER_HOLDOFF_RDWR         2
// #define BUFFER_DELAY_RDWR           3
// #define BUFFER_SELFRESET_RDWR	    4
// #define BUFFER_NTRIGGERS_RD         5
// #define BUFFER_STATE_RD             6
// #define	BUFFER_HASEVENT_RD    	    7

// #define MAGIC_NUMBER_RD 8'b11111111;
// #define MAGIC_NUMBER_VALUE 8'b10101111;

// #define WB_SLAVE_HISTOGRAM_ADDR 8'b00000100

// #define GATE0_DEFAULT 16'b0000000000001111
// #define GATEN_DEFAULT 16'b0000000011111111
// #define STAGEN_DEFAULT 6


// #define DACEEPROM_DEFAULT 0;
// #define DACACTIVE_DEFAULT 1;

// #define HVTARGET_DEFAULT 0;
// #define HVLIMIT_DEFAULT 1250;

// #define HVRAMPSPEED_DEFAULT 255;
// #define THRESHOLD1_DEFAULT 500;
// #define THRESHOLD2_DEFAULT 1200;


// #define DELAYTIME_DEFAULT 2300
// #define HOLDOFFTIME_DEFAULT 0
// #define FORCECMD_DEFAULT 0

// #define GATE0_DEFAULT 255
// #define GATEN_DEFAULT 65535


// #define GATE0_ADDR0 0
// #define GATE0_ADDR1 1
// #define GATEN_ADDR0 2
// #define GATEN_ADDR1 3
// #define STAGEN_ADDR 4
// #define RAMREAD_ADDR 5
// #define RAMSELE_ADDR 6
// #define RAMRDD_ADDR1 7
// #define RAMRDD_ADDR0 8
// #define NTRIGS_ADDR1 9
// #define NTRIGS_ADDR0 10

// #define LIVETM_ADDR5 11
// #define LIVETM_ADDR4 12
// #define LIVETM_ADDR3 13
// #define LIVETM_ADDR2 14
// #define LIVETM_ADDR1 15
// #define LIVETM_ADDR0 16

// #define DEADTM_ADDR5 17
// #define DEADTM_ADDR4 18
// #define DEADTM_ADDR3 19
// #define DEADTM_ADDR2 20
// #define DEADTM_ADDR1 21
// #define DEADTM_ADDR0 22

// #define DELAYT_ADDR1 23
// #define DELAYT_ADDR0 24
// #define HOLDOT_ADDR1 25
// #define HOLDOT_ADDR0 26
// #define BSTATEC_ADDR 27
// #define BCONFIG_ADDR 28
// #define BSTATEF_ADDR 29

// #define RAMREAD_DEFAULT 0
// #define RAMSELE_DEFAULT 0
// #define DELAYT_DEFAULT 2300
// #define HOLDOT_DEFAULT 0
// #define BCONFIG_DEFAULT 1
// #define BSTATEF_DEFAULT 0

// #define HISTOG_ADDR1 30
// #define HISTOG_ADDR0 31
// #define TOTCUR_ADDR1 32
// #define TOTCUR_ADDR0 33
// #define HISTRST_ADDR 34

// #define I2CACTIVE_ADDR 35
// #define HVTARGET_ADDR 36
// #define HVLIMIT_ADDR 37
// #define RAMPSPEED_ADDR 38
// #define THRESHOLD1_ADDR 39
// #define THRESHOLD2_ADDR 40
// #define EEPROMCHOICE_ADDR 41

#define SIGNAL_INPUT_CONFIG_DEFAULT 1
#define EDGE_TRIGGER_CONFIG_DEFAULT 3
#define TOT_WINDOW_SHORT_DEFAULT 50
#define TOT_WINDOW_LONG_DEFAULT 25
#define TOT_TRIGGER_CONFIG_DEFAULT 50
#define FILTER_TRIGGER_CONFIG_DEFAULT 4
#define TRIGGER_HANDLER_CONFIG_DEFAULT 99

#define FPGA_I2C_ADDRESS 0x55
#define I2C_REG_SIGNAL_INPUT_CONFIG 0x01
#define I2C_REG_EDGE_TRIGGER_CONFIG 0x02
#define I2C_REG_TOT_WINDOW_SHORT_MSB 0x03
#define I2C_REG_TOT_WINDOW_SHORT_LSB 0x04
#define I2C_REG_TOT_WINDOW_LONG_MSB 0x05
#define I2C_REG_TOT_WINDOW_LONG_LSB 0x06

// 0x01: o_reg_SIGNAL_INPUT_CONFIG[7:0]  <= input_shift;
//                 0x02: o_reg_EDGE_TRIGGER_CONFIG[7:0]  <= input_shift;
//                 0x03: o_reg_TOT_WINDOW_SHORT[15:8]  <= input_shift;
//                 0x04: o_reg_TOT_WINDOW_SHORT[7:0]  <= input_shift;
//                 0x05: o_reg_TOT_WINDOW_LONG[15:8]  <= input_shift;
//                 0x06: o_reg_TOT_WINDOW_LONG[7:0]  <= input_shift;
//                 0x07: o_reg_TOT_TRIGGER_CONFIG[15:8]  <= input_shift;
//                 0x08: o_reg_TOT_TRIGGER_CONFIG[7:0]  <= input_shift;
//                 0x09: o_reg_FILTER_TRIGGER_CONFIG[15:8]  <= input_shift;
//                 0x0B: o_reg_FILTER_TRIGGER_CONFIG[7:0]  <= input_shift;
//                 0x0C: o_reg_TRIGGER_HANDLER_CONFIG[15:8]  <= input_shift;
//                 0x0D: o_reg_TRIGGER_HANDLER_CONFIG[7:0]  <= input_shift;
//                 0x0E: o_reg_DAC_CONTROL_CONFIG[95:88] <= input_shift;
//                 0x0F: o_reg_DAC_CONTROL_CONFIG[87:80] <= input_shift;
//                 0x10: o_reg_DAC_CONTROL_CONFIG[79:72] <= input_shift;
//                 0x11: o_reg_DAC_CONTROL_CONFIG[71:64] <= input_shift;
//                 0x12: o_reg_DAC_CONTROL_CONFIG[63:56] <= input_shift;
//                 0x13: o_reg_DAC_CONTROL_CONFIG[55:48] <= input_shift;
//                 0x14: o_reg_DAC_CONTROL_CONFIG[47:40] <= input_shift;
//                 0x15: o_reg_DAC_CONTROL_CONFIG[39:32] <= input_shift;
//                 0x16: o_reg_DAC_CONTROL_CONFIG[31:24] <= input_shift;
//                 0x17: o_reg_DAC_CONTROL_CONFIG[23:16] <= input_shift;
//                 0x18: o_reg_DAC_CONTROL_CONFIG[15:8] <= input_shift;
//                 0x19: o_reg_DAC_CONTROL_CONFIG[7:0] <= input_shift;

#endif


