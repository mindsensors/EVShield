/************************************************************************/
/*                                                                 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  History:
  Date      Author          Comments
  Mar 2017  Seth Tenembaum  initial

************************************************************************/

// this example shows more advanced graphics functions, including bitmaps/sprites and fonts
// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

#include <Fonts/FreeSerifItalic24pt7b.h>
// for the included font options, see Documents\Arduino\libraries\Adafruit_GFX_Library\Fonts

// this is a sprite represented as a literal in code
// 0 will skip that pixel, leaving whatever color was there
// 1 will fill in that pixel with the color specified when drawn
// B indicates a binary literal
// you could also use a tool to convert an image file
// RAM is limited, so PROGMEM will include this data in the program, it will not change
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
    
    // here we draw some copies of the bitmap: what do these arguments mean?
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
    // print 150 from the top to not mess up the bitmap drawings, and 5 pixels from the left edge as a little margin
    uim.setCursor(5, 150);
    uim.println("Nice fonts");
}

void loop3() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // no need to repeat anything in this example, just wait for GO to reset
}
