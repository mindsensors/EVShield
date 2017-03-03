#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_LineLeader.h>

EVs_LineLeader ll;

void setup1() {
    uim.println("SumoEyes sensor test");
    ll.init(&ev, SH_BAS1);
    
    uim.setCursor(0, 2*16);
    uim.printf("firmware: %s\n",  ll.getFirmwareVersion());
    uim.printf("device ID: %s\n", ll.getDeviceID());
    uim.printf("vendor ID: %s\n", ll.getVendorID());
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    uim.clearLine(6);
    uim.setCursor(0, 5*16);
    char s[9];
    format_bin(ll.getResult(), s);
    uim.print("sensor array: ");
    uim.println(s);
}
