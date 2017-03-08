// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <Fonts/FreeSerifItalic24pt7b.h>

// 0 will skip that pixel, leaving whatever color was there
// 1 will fill in that pixel with the specified color
const PROGMEM uint8_t bitmap[] = {
    B11111111,B11111111,
    B10000000,B00000001,
    B10001000,B00010001,
    B10001000,B00010001,
    B10001000,B00010001,
    B10001000,B00010001,
    B10000000,B00000001,
    B10000000,B00000001,
    B10000101,B10100001,
    B10000010,B01000001,
    B10000000,B00000001,
    B11111111,B11111111
};

void setup3() {
    // ev and uim have already been instantiated, you can just use them now.
    ev.ledSetRGB(0, 0, 0); // ev = EVShield
    
    // draw starting at x,y coordinate 10,10 as the top left
    // the bitmap is 16 pixels wide by 12 pixels tall
    uim.drawBitmap(10, 10, bitmap, 16, 12, EVs_UIM_GREEN);
    uim.drawBitmap(50, 10, bitmap, 16, 12, EVs_UIM_BLUE);
    uim.drawBitmap(100, 10, bitmap, 16, 12, EVs_UIM_RED);
    uim.drawBitmap(200, 10, bitmap, 16, 12, EVs_UIM_YELLOW);
    
    uim.setFont(&FreeSerifItalic24pt7b);
    // don't scale the font
    // text size 2, the default, would draw each pixel as 4 pixels in a 2x2 square
    uim.setTextSize(1);
    // print 150 from the top to not mess up the bitmap drawings, and 2 pixels from the left edge as a little margin
    uim.setCursor(2, 150);
    uim.println("Nice fonts");
}

void loop3() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // your creative code here
}
