#!/bin/sh
apio clean
apio build 
datev=$(date  +"%y%m%d-%H%M")
cp ../fw.h ../fw_backups/fw_${datev}.h
echo -n "const " > ../fw.h && xxd -i hardware.bin >> ../fw.h
python3 gen_header.py > ../fpga_defs.h
