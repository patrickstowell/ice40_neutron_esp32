import hashlib
import base64

def hash6_base64(input_str):
    hash_bytes = hashlib.sha256(input_str.encode()).digest()
    val = base64.urlsafe_b64encode(hash_bytes).decode()[:6]
    val = val.replace("-","A")
    val = val.replace("_","B")
    return "C" + val



f = open("module_memory.h", 'w')

f.write("// Auto-generated File, do not edit!\n");
f.write("#pragma once\n")
f.write("#include \"utilities.h\"\n")
f.write("#include \"module_config.h\"\n")
f.write("using namespace CONFIG;\n")


f.write("\n")
f.write("namespace MEMORY {\n")
f.write("  Preferences eeprom;\n")
varlist = []
namlist = []
vallist = []

for line in open("module_config.h"):
  if "RTC_DATA_ATTR" not in line: continue
  if not "EEPROM" in line: continue
  line = line.split("//")[0]

  vartype = "Int"
  if "bool " in line: vartype = "Bool"
  if "uint " in line: vartype = "UInt"
  if "String " in line: vartype = "String"

  nam = line.strip().replace("RTC_DATA_ATTR","")
  nam = nam.replace("bool","")
  nam = nam.replace("int64_t","")
  nam = nam.replace("int ","")
  nam = nam.replace("uint8_t","")
  nam = nam.replace("String", "")
  nam = nam.replace(";", "")
  nam = nam.split("=")[0].strip()
  
  val = line.strip().split("=")[-1].replace(";","").strip()

  print(vartype, nam, val)
  varlist.append(vartype)
  namlist.append(nam)
  vallist.append(val)

f.write("  void Print() {\n")
for i in range(len(varlist)):
  nam = namlist[i]
  f.write(f"    Serial.print(\"{nam} : \");\n")
  f.write(f"    Serial.println({nam});\n")
f.write("  }\n")


f.write("  void ReadFromEEPROM() {\n")
for i in range(len(varlist)):
  nam = namlist[i]
  var = varlist[i]
  vhash = hash6_base64(nam + var)
  f.write(f"    {nam} = eeprom.get{var}((\"{vhash}\"));\n")
f.write("  }\n")

f.write("  void WriteToEEPROM() {\n")
for i in range(len(varlist)):
  nam = namlist[i]
  var = varlist[i]
  val = vallist[i]
  vhash = hash6_base64(nam + var)

  f.write(f"    eeprom.put{var}((\"{vhash}\"), {nam});\n")
f.write("  }\n")

f.write("  void Command(String message) {\n")
f.write("    String parts[2];\n")
f.write("    splitMessage(message, parts, 2);\n")

for i in range(len(varlist)):
  nam = namlist[i]
  var = varlist[i]
  val = vallist[i]
  vhash = hash6_base64(nam + var)
  toconv = ""


sdadsa DONT NEED TO PUT TO EEPROM, JUST CHANGE LOCALLY, and HAVE A COMMAND TO UPDATE EEPROM AFTERWARDS? OR MODIFY BOTH.

  if i == 0:
    f.write(f"    if(parts[0] == F(\"{nam}\")) eeprom.put{var}((\"{vhash}\"), parts[1].to{var}());\n")
  else:
    f.write(f"    else if(parts[0] == F(\"{nam}\")) eeprom.put{var}((\"{vhash}\"), parts[1].to{var}());\n")


f.write("  return\n")
f.write("}\n")

f.write("""
        
  bool begin() {
    Serial.println("Memory::begin()");
    if (BOOT_COUNT == 0){

        eeprom.begin("config", false);
        eeprom.putUInt("hasconfig", 0);

        if (!eeprom.getUInt("hasconfig", 0)) {
            Serial.println("Memory::CheckEEPROMValid() : Uploading EEPROM Defaults");
            eeprom.clear();
            Print();

            WriteToEEPROM();

            eeprom.putUInt("hasconfig", 1);
        } else {
            Serial.println("Memory::CheckEEPROMValid() : EEPROM Already Present!");

        }

        int value = eeprom.getUInt("hasconfig", 0);
        if (value) ReadFromEEPROM();
        eeprom.end();

    }

    Print();
    BOOT_COUNT += 1;
    return true;
  }

  bool handle() { 
      return true; 
  }

}
""")

f.write("}\n")
