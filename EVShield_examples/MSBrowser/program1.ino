#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_EV3Touch.h>

EVs_EV3Touch myTouch;

void setup1() {
    uim.println("EV3 touch sensor test");
    myTouch.init(&ev, SH_BAS1);
}

void loop1() {
    if (ev.isTouched()) ESP.reset();
    
    if (myTouch.isPressed())
        uim.writeLine(0, 3, "pressed", true, EVs_UIM_WHITE);
    else
        uim.writeLine(0, 3, "released", true, EVs_UIM_WHITE);
    
    uim.clearLine(4);
    uim.setCursor(0, 3*16);
    uim.printf("bump count: %u", myTouch.getBumpCount());
}
