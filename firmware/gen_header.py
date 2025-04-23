
print("#ifndef FPGA_PIN_DEF_h")
print("#define FPGA_PIN_DEF_h")
print("")
f = open("board.pcf")
for line in f:
    line = line.strip()
    if line.startswith("#"): continue
    if line == "": continue
    line = line.replace("set_io ", "#define FPGA_PIN_")
    print(line)
print("")
print("#endif")


f = open("parameters.v")
for line in f:
  line = line.strip()
  cppline = line.replace("`define", "#define")
  cppline = cppline.replace("`ifndef", "#ifndef")
  cppline = cppline.replace("`endif", "#endif")
  cppline = cppline.replace("8'h",'0x')
  cppline = cppline.replace("7'h",'0x')
  print(cppline)
