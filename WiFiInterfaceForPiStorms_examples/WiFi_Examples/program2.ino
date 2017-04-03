/*
    This program builds off of program1.
    Now you will see a form when you open the webpage. You can enter a number of rotations
    and hit Submit. Then you will be directed to a different webpage and it will spin that many times.
    This uses GET to pass parameters (here the number of rotations) through the URL.
*/

// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <ESP8266WebServer.h>

// The `server` was already declared in program1. It was declared as a global variable,
// meaning we can access it here. program1 won't be running when program2 is, 
// so we don't have to worry about conflicts there.

void setup2() {
    server.on("/", [](){
        // This is an example of a lambda function. It is a method without a name (anonymous) defined and used right here.
        // You could, of course use a method similar to handleRunMotorRequest from program1 if you prefer.
        
        // Here we use a long string that would take up a lot of space in SRAM, 
        // so we use F("this") macro to put it in flash memory where there is a lot more space.
        // You have a full megabyte for your program, but just shy of 82 kilobytes for global variables. Better not waste it!
        // Here we are saving 288 bytes. If you wanted to be really efficient you could remove all the whitespace 
        // and put everything on one line, but you really shouldn't have any problems running out of flash memory here.
        
        // To make it easier to read there is a single string across multiple lines. The backslash at the end of the line
        // tells the compiler that this line isn't done yet, append the next line here.
        // We're using single quotes because they are in a string defined by double quotes.
        // HTML accepts them just fine, but if you wanted to use a double quote you would need to escape it like this: \"
        // to make it explicit that you want a quotation mark inside of your string, not to end your string here.
        // The action for the form here is /move. When you hit Submit, it will take you to that page,
        // along with the form data. The input has the name "rotations", so you'll see that in the url.
        server.send(200, "text/html", F("<form action='/move'> \
                                            Rotations: <br> \
                                            <input type='number' name='rotations' min='1' max='255'> <br> \
                                            <input type='submit'> \
                                        </form>"));
    });
    
    // Here a separate webpage, move, is defined. You can have many different paths for the server to look for.
    server.on("/move", [](){
        // This takes the "rotations" parameter submitted from the form.
        // It also converts it from a string to an interger.
        uint8_t rotations = server.arg("rotations").toInt();
        ev.bank_a.motorRunRotations(SH_Motor_1, SH_Direction_Forward, SH_Speed_Slow,
                                    rotations, SH_Completion_Dont_Wait, SH_Next_Action_Float);
        // Also write how many rotations it recieved on the screen
        uim.writeLine(0, 5, String(rotations).c_str(), true, EVs_UIM_CYAN);
        // The back link links to "/", the root webpage
        server.send(200, "text/html", F("<p>rotating...</p> <br> \
                                         <a href='/'>back</a>"));
    });
    
    server.begin();
    
    uim.println("My IP address is:");
    uim.println(WiFi.localIP());
    
    uim.println("\nRotations: \n0");
}

void loop2() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    server.handleClient();
}
