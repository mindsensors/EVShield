// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

void setup2() {
    // ev and uim have already been instantiated, you can just use them now.
    ev.ledSetRGB(0, 0, 0); // ev = EVShield
    uim.println("Drawing"); // uim = UI Module
    
    // uim.begin() has already been called for you, don't call it again
    
    // fills the screen with black (not necessary here)
    uim.clearScreen();
    
    // if your project puts your PiStorms mounted in a different orientation, you can rotate the screen
    //uim.setRotation(3);
    // 0: left, portrait, bank A at the top, bank B at the bottom
    // 1: upside-down, landscape, GO button is at the top (above screen) and all the text printed on the case is upside-down
    // 2: right, portrait, bank B at the top, bank A at the bottom
    // 3: right-side-up, landscape, GO button below screen, the text printed on the case is readable 
    
    // takes half-a-second
    // put in some short delays to let the ESP8266 catch up
    // if you find it crashing from continuously drawing
    uim.fillScreen(EVs_UIM_WHITE);
    delay(1);
    
    // 100 pixels across, 20 down, rectangle has a width of 50 and a height of 30
    uim.fillRect(100, 20, 50, 30, EVs_UIM_BLUE);
    
    // see also: File -> Examples -> Adafruit ILI9340 -> graphicstest
    // https://learn.adafruit.com/adafruit-gfx-graphics-library
}

void loop2() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // your creative code here
}
