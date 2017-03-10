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

// this example will cover many uses of text and different colors
// remember to update credentials.h so the device can connect to your network!

#include <EVShield.h>
#include <EVs_UIModule.h>

void setup1() {
    // ev and uim have already been instantiated, you can just use them now.
    ev.ledSetRGB(0, 0, 0); // ev = EVShield
    uim.println("Text and colors\n"); // uim = UI Module
    
    uim.setTextColor(EVs_UIM_MAGENTA);
    uim.println("You can call .println directly on a UI Module instance!");
    
    // x = 0 is the left side of the screen, 8 means the 8th line of text from the top, true is to clear anything that was there before
    uim.writeLine(0, 8, "If you want to print at a specific line number, use .writeLine", true, EVs_UIM_CYAN);
    // this could be useful if you want to update the value on a line, as it can clear whatever was there before
    
    // this will be just below the writeLine text, and printed in cyan
    uim.println("Ta-da!");
    
    // a very dark blue on bright green
    uim.setTextColor(uim.Color565(0,0,60), uim.Color565(30,255,30));
    uim.println("You can also use custom colors and set a background color.");
    
    // predefined colors:
    // EVs_UIM_BLACK
    // EVs_UIM_BLUE
    // EVs_UIM_RED
    // EVs_UIM_GREEN
    // EVs_UIM_CYAN
    // EVs_UIM_MAGENTA
    // EVs_UIM_YELLOW
    // EVs_UIM_WHITE
    
    // if not specified, the background color will default to black
    uim.setTextColor(EVs_UIM_YELLOW);
    // besides .setTextColor, you can also move the cursor by pixels
    uim.setCursor(260, 8);
    // and set text size
    uim.setTextSize(1);
    uim.println("mini text");
    uim.setCursor(60, 76);
    uim.setTextSize(3);
    uim.println("big text");
    // you can also use fonts, see program3
}

void loop1() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // no need to repeat anything in this example, just wait for GO to reset
}
