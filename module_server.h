class module_webserver {
private:
    WebServer server{80};
    bool ledState = false;

public:
    bool begin() {
        server.on("/", [this]() {
            String html = "<html><head><title>ESP32 Control</title></head><body>";
            html += "<h1>ESP32 Control Panel</h1>";
            html += "<p>LED is " + String(ledState ? "ON" : "OFF") + "</p>";
            html += "<form method='GET' action='/toggle'><button type='submit'>Toggle LED</button></form>";
            html += "</body></html>";
            server.send(200, "text/html", html);
        });

        server.on("/toggle", [this]() {
            ledState = !ledState;
            Serial.println("LED State toggled: " + String(ledState ? "ON" : "OFF"));
            server.sendHeader("Location", "/", true);
            server.send(302, "text/plain", "");
        });

        server.begin();
        Serial.println("Web server started");
        return true;
    }

    bool handle() {
        server.handleClient();
        return true;
    }

    bool getLEDState() const {
        return ledState;
    }
};

module_webserver WEB;