
class fpga_signal_input : public fpga_module  {
public:
  void upload(){
    uint8_t val = 0;
    val |= enable_ch1 << 0;
    val |= enable_ch2 << 1;
    val |= invertlogic_ch1 << 2;
    val |= invertlogic_ch2 << 3;
    val |= edgeonly_ch1 << 4;
    val |= edgeonly_ch2 << 5;
    val |= pulser_ch1 << 6;
    val |= pulser_ch2 << 7;
    set8(I2C_REG_SIGNAL_INPUT_CONFIG, val);
  }

  void download(){
    uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
    enable_ch1 = (val >> 0) & 0x01;
    enable_ch2 = (val >> 1) & 0x01;
    invertlogic_ch1 = (val >> 2) & 0x01;
    invertlogic_ch2 = (val >> 3) & 0x01;
    edgeonly_ch1 = (val >> 4) & 0x01;
    edgeonly_ch2 = (val >> 5) & 0x01;
    pulser_ch1 = (val >> 6) & 0x01;
    pulser_ch2 = (val >> 7) & 0x01;
  }

  void print() {
    uint8_t val = get8(I2C_REG_SIGNAL_INPUT_CONFIG);
    compare("Enable CH1 : ", enable_ch1, (val >> 0) & 0x01);
    compare("Enable CH2 : ", enable_ch2, (val >> 1) & 0x01);
    compare("Invert CH1 : ", invertlogic_ch1, (val >> 2) & 0x01);
    compare("Invert CH2 : ", invertlogic_ch2, (val >> 3) & 0x01);
    compare("EdgeOnly CH1 : ", edgeonly_ch1, (val >> 4) & 0x01);
    compare("EdgeOnly CH2 : ", edgeonly_ch2, (val >> 5) & 0x01);
    compare("Pulser CH2 : ", pulser_ch1, (val >> 6) & 0x01);
    compare("Pulser CH2 : ", pulser_ch2, (val >> 7) & 0x01);
  }

  bool enable_ch1; // - 0 enable 1
  bool enable_ch2; // - 1 enable 2
  bool invertlogic_ch1; // - 2 invert logic 1
  bool invertlogic_ch2; // - 3 invert logic 2
  bool edgeonly_ch1; // - 4 edge only
  bool edgeonly_ch2; // - 5 edge only
  bool pulser_ch1; // - 6 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
  bool pulser_ch2; // - 7 Pulser : Simulate Combined Pulse [Every 2048 clock cycles]
};

fpga_signal_input sigin;