apio clean
apio build
echo -n "const " > fw.h && xxd -i hardware.bin >> fw.h
