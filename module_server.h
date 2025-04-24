// #include <WiFi.h>
// #include "module_memory.h"
// #include <Arduino.h>
// #include <WiFi.h>
// #include <AsyncTCP.h>
// #include <ESPAsyncWebServer.h>
// #include <WebSerial.h>

namespace SERVER {

    // AsyncWebServer* server;//(80);

    // void recvMsg(uint8_t *data, size_t len){
    //     WebSerial.println("Received Data...");
    //     String d = "";
    //     for(int i=0; i < len; i++){
    //         d += char(data[i]);
    //     }
    //     WebSerial.println(d);
    //     if (d == "ON"){
    //         Serial.println("ON");
    //     }
    //     if (d=="OFF"){
    //         Serial.println("OFF");
    //     }
    // }

    bool begin() {
        if (!MEMORY::SERVER_ENABLED) return true;
        // server = new AsyncWebServer(80);
        // WebSerial.begin(server);
        // WebSerial.msgCallback(recvMsg);
        // server->begin();
        return true;
    }

    bool handle() {
        if (!MEMORY::SERVER_ENABLED) return true;
        // WebSerial.println("Hello!");
        // delay(1000);
        return true;
    }

}
