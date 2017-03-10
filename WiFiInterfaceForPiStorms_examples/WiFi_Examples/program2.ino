// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <ESP8266WebServer.h>

// server was already declared in program1
// it is a global variable
// program1 won't be running when program2 is, so we can use it here safely

void setup2() {
    server.on("/", [](){
        server.send(200, "text/html", F("<form action=\"/move\">Rotations: <br><input type=\"text\" name=\"rotations\"> <br><input type=\"submit\"></form>"));
    });
    server.on("/move", [](){
        uint8_t rotations = atoi(server.arg("rotations").c_str());
        ev.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,
                                    rotations, SH_Completion_Dont_Wait, SH_Next_Action_Float);
        server.send(200, "text/html", F("rotating... <br><a href=\"/\">back</a>"));
    });
    server.begin();
    
    uim.println("My IP address is:");
    uim.println(WiFi.localIP());
}

void loop2() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    server.handleClient();
}
