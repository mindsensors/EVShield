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

// this example will cover filling the screen and drawing basic shapes
// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

void setup2() {
    // ev and uim have already been instantiated, you can just use them now.
    ev.ledSetRGB(0, 0, 0); // ev = EVShield
    uim.println("Drawing"); // uim = UI Module
    
    // uim.begin() has already been called for you, don't call it again
    
    // fills the screen with black (not necessary here, it's already blank)
    uim.clearScreen();
    
    // if your project puts your PiStorms mounted in a different orientation, you can rotate the screen
    //uim.setRotation(3);
    // 0: left, portrait, bank A at the top, bank B at the bottom
    // 1: upside-down, landscape, GO button is at the top (above screen) and all the text printed on the case is upside-down
    // 2: right, portrait, bank B at the top, bank A at the bottom
    // 3: right-side-up, landscape, GO button below screen, the text printed on the case is readable 
    
    // calling .fillScreen takes half of a second
    // put in some short delays to let the ESP8266 catch up if you find it crashing from continuously drawing
    uim.fillScreen(EVs_UIM_WHITE);
    delay(1);
    
    // 100 pixels across, 20 down, rectangle has a width of 50 and a height of 30
    uim.fillRect(100, 20, 50, 30, EVs_UIM_BLUE);
    // use drawRect instead of filLRect to only draw the border and not fill it in
    
    // you can draw lines, circles, triangles, and rounded rectangles much the same way
    // https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
    
    // see also: File -> Examples -> Adafruit ILI9340 -> graphicstest
    // NOTE! This program will not run. You would have to change _cs, _dc, and _rst to D1, D4, and -1
    // Even still, it will crash. This program does not include delays between long drawing functions
    // which doesn't let the ESP8266 keep WiFi and everything else running. It can get through 2-3 `fillScreen`s
    // before it's been too long to recover.
}

void loop2() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // no need to repeat anything in this example, just wait for GO to reset
}
