// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleRunMotorRequest() {
    ev.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,
                                3, SH_Completion_Dont_Wait, SH_Next_Action_Float);
    server.send(200, "text/plain", "rotating...");
}

void setup1() {
    server.on("/", handleRunMotorRequest);
    server.begin();
    
    uim.println("My IP address is:");
    uim.println(WiFi.localIP());
}

void loop1() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    server.handleClient();
}
