#include <EVShield.h>
#include <EVs_UIModule.h>

#include "MSBrowser.h"

void setup1() {
    uim.println("Button tests");
}

void loop1() {
    if (ev.isTouched()) ESP.reset();
    
    if (ev.getButtonState(BTN_GO))
        uim.writeLine(0, 3, "GO is pressed", true, EVs_UIM_WHITE); // left edge, first line, text, do clear line, white text
    else
        uim.writeLine(0, 3, "GO is not pressed", true, EVs_UIM_WHITE);
    
    if (ev.getButtonState(BTN_LEFT))
        uim.writeLine(0, 4, "Left is pressed", true, EVs_UIM_WHITE);
    else
        uim.writeLine(0, 4, "Left is not pressed", true, EVs_UIM_WHITE);
    
    if (ev.getButtonState(BTN_RIGHT))
        uim.writeLine(0, 5, "Right is pressed", true, EVs_UIM_WHITE);
    else
        uim.writeLine(0, 5, "Right is not pressed", true, EVs_UIM_WHITE);
    
    uim.writeLine(0, 7, "EVs_UIModule\n  .getButtonState: ", false, EVs_UIM_WHITE);
    uim.print(uim.getButtonState(EVs_BTN_LEFT));
    uim.print(uim.getButtonState(EVs_BTN_RIGHT));
    uim.print(uim.getButtonState(EVs_BTN_UP));
    uim.print(uim.getButtonState(EVs_BTN_DOWN));
    uim.print(uim.getButtonState(EVs_BTN_CLICK));
}
