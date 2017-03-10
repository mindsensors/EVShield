/*
    This program demonstrates how you can have many different actions for different URLs.
*/

// Remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <ESP8266WebServer.h>

// The `server` was already declared in program1. It was declared as a global variable,
// meaning we can access it here. program1 won't be running when program2 is, 
// so we don't have to worry about conflicts there.

void setup3() {
    
    server.on("/on", [](){
        // This is an example of a lambda function. It is a method without a name (anonymous) defined and used right here.
        // You could, of course use a method similar to handleRunMotorRequest from program1 if you prefer.
        ev.ledSetRGB(0, 0, 255);
        server.send(200, "text/plain", "LEDs on!");
    });
    
    server.on("/off", [](){
        ev.ledSetRGB(0, 0, 0);
        server.send(200, "text/plain", "LEDs off");
    });
    
    server.on("/right", [](){
        ev.bank_a.ledSetRGB(0, 255, 0);
        ev.bank_b.ledSetRGB(0, 0, 0);
        server.send(200, "text/plain", "Right LED on");
    });
    
    server.on("/left", [](){
        ev.bank_a.ledSetRGB(0, 0, 0);
        ev.bank_b.ledSetRGB(255, 0, 0);
        server.send(200, "text/plain", "Left LED on");
    });
    
    server.begin();
    
    uim.println("My IP address is:");
    uim.println(WiFi.localIP());
    uim.println();
    uim.println("Open a web browser and go to any of the following:");
    uim.println();
    uim.print(WiFi.localIP());
    uim.println("/on");
    uim.print(WiFi.localIP());
    uim.println("/off");
    uim.print(WiFi.localIP());
    uim.println("/right");
    uim.print(WiFi.localIP());
    uim.println("/left");
    
}

// .handleClient will take care of everything to reply to HTTP requests
// Remember this is in the loop! We want to continually handle requests.
void loop3() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    server.handleClient();
}
