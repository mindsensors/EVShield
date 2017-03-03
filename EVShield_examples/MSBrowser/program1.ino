#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_LineLeader.h>

EVs_LineLeader ll;

void setup1() {
    uim.println("SumoEyes sensor test");
    ll.init(&ev, SH_BAS1);
    
    uim.setCursor(0, 2*16);
    uim.println(ll.getFirmwareVersion());
    uim.println(ll.getDeviceID());
    uim.println(ll.getVendorID());
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    uim.clearLine(6);
    uim.setCursor(0, 5*16);
    uint8_t result = ll.getResult();
    uim.print("sensor array: ");
    for (uint8_t i = 0; i++; i < 8)
        uim.print(result && 1 << i);
}
