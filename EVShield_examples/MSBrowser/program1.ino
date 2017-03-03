#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_NXTTouch.h>

EVs_NXTTouch myTouch;

void setup1() {
    uim.println("NXT touch sensor test");
    myTouch.init(&ev, SH_BAS1);
}

void loop1() {
    if (ev.isTouched()) ESP.reset();
    
    if (myTouch.isPressed())
        uim.writeLine(0, 3, "pressed", true, EVs_UIM_WHITE);
    else
        uim.writeLine(0, 3, "released", true, EVs_UIM_WHITE);
}
