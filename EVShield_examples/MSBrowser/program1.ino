#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_EV3Infrared.h>

EVs_EV3Infrared myIR;

void setup1() {
    uim.println("EV3 infrafred sensor test");
    myIR.init(&ev, SH_BAS1);
    myIR.setMode(MODE_Infrared_Proximity);
    
    uim.setCursor(0, 4*16);
    uim.print("proximity: ");
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    // if (myUS.detect())
    //     uim.writeLine(0, 3, "Device found", true, EVs_UIM_WHITE);
    // else
    //     uim.writeLine(0, 3, "No device found", true, EVs_UIM_WHITE);
    
    uim.clearLine(6);
    uim.setCursor(0, 5*16);
    uim.println(myIR.readProximity());
}
