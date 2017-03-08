// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <Fonts/FreeSans24pt7b.h>

void printCenteredText(uint16_t minX, uint16_t minY, uint16_t maxX, uint16_t maxY, char *text) {
    int16_t  x, y;
    uint16_t w, h;
    uim.getTextBounds(text, 0, 0, &x, &y, &w, &h);
    uim.setCursor((((maxX-minX)-w)/2)+minX, (((maxY-minY)-h)/2)+minY+h);
    uim.print(text);
}

void setup3() {
    // ev and uim have already been instantiated, you can just use them now.
    ev.ledSetRGB(0, 0, 0); // ev = EVShield
    
    uim.setFont(&FreeSans24pt7b);
    uim.setTextSize(1);
    // find the height of the text to know where to set the cursor so it's not cut off
    // int16_t  x, y;
    // uint16_t w, h;
    // uim.getTextBounds("setup3", 0, 120, &x, &y, &w, &h);
    // uim.setCursor(0, h);
    // uim.println("setup3"); // uim = UI Module
    printCenteredText(160, 0, 170, 120, "setup3---------");
}

void loop3() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // your creative code here
}
