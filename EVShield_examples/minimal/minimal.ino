#include <EVShield.h>
#include <EVs_UIModule.h>
#include <ArduinoOTA.h>

const char* ssid     = "your_WiFi_network";
const char* password = "letmein";
const char* uploadPassword = "upload";

EVShield ev;
EVs_UIModule uim;

void setup() {
    Serial.begin(115200);
    Serial.println();
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) yield();
    ArduinoOTA.setPassword(uploadPassword);
    ArduinoOTA.begin();
    
    ev.init();
    uim.begin();
    uim.clearScreen();
    uim.fillRect(1, 1, 10, 10, uim.Color565(255,0,0));
}

void loop() {
    delay(1);
}
