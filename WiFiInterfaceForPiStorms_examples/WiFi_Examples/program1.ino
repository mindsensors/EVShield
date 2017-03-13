/*
    This program will host a web server from the Wi-Fi Arduino Interface for PiStorms.
    When the program starts, it will print its IP on screen.
    If you type that in a web browser, you will see "rotating..." on the page
    and the motor on BAM1 spin slowly for 3 rotations. Refresh to see it again.
*/

// Remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <ESP8266WebServer.h>

// Declare a new ESP8266WebServer object that will listen on port 80, the standard for HTTP.
ESP8266WebServer server(80);

// This is the function that will be called when the server recieves a request.
// It will rotate the motor and reply to the request.
// It sends a status code 200, which means OK (see www.restapitutorial.com/httpstatuscodes.html).
// The content type it is replying with is text, and just plain text.
// You may want to change this to "text/html" if you want to have a more involved page with HTML.
// Try changing this and making it your own!
void handleRunMotorRequest() {
    ev.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,
                                3, SH_Completion_Dont_Wait, SH_Next_Action_Float);
    server.send(200, "text/plain", "rotating...");
}

// All of the object have already been initialized elsewhere.
// Here we tell the server that on recieving a request for "/", the root webpage
// (just the ip address, no path following it) it should run the handleRunMotorRequest method.
// Now that the server is set up (simple, no?) we call .begin to get it going.
// Finally we print the device's IP to the screen so you can access it.
void setup1() {
    server.on("/", handleRunMotorRequest);
    server.begin();
    
    uim.println("My IP address is:");
    uim.println(WiFi.localIP());
}

// .handleClient will take care of everything to reply to HTTP requests
// Remember this is in the loop! We want to continually handle requests.
void loop1() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    server.handleClient();
}
