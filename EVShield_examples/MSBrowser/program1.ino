#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_EV3Infrared.h>

EVs_EV3Infrared myIR;

void setup1() {
    uim.println("EV3 infrafred sensor test");
    myIR.init(&ev, SH_BAS1);
    myIR.setMode(MODE_Infrared_Remote);
    
    uim.setCursor(0, 2*16);
    uim.print("button: ");
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    uim.clearLine(4);
    uim.setCursor(0, 3*16);
    uim.println(myIR.readChannelButton(1));
}
