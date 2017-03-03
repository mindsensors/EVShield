#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_EV3Ultrasonic.h>

EVs_EV3Ultrasonic myUS;

void setup1() {
    uim.println("EV3 ultrasonic sensor test");
    myUS.init(&ev, SH_BAS1);
    myUS.setMode(MODE_Sonar_Inches);
    
    uim.setCursor(0, 4*16);
    uim.print("distance: ");
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    if (myUS.detect())
        uim.writeLine(0, 3, "Device found", true, EVs_UIM_WHITE);
    else
        uim.writeLine(0, 3, "No device found", true, EVs_UIM_WHITE);
    
    uim.clearLine(6);
    uim.setCursor(0, 5*16);
    uim.println(myUS.getDist());
}
