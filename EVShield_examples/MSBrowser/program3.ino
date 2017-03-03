#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_AbsoluteIMU.h>

EVs_AbsoluteIMU imu;

void setup3() {
    imu.init(&ev, SH_BAS1);
    
    uim.println(imu.getFirmwareVersion());
    uim.println(imu.getDeviceID());
    uim.println(imu.getVendorID());
    uim.fillRect(0, 16*4, 320, 16, EVs_UIM_WHITE);
}

void loop3() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    accl myaccl;
    imu.readAccelerometer(myaccl);
    int val = 318 * myaccl.tx / 256;
    /*if (val>0)*/ uim.fillRect(1, 16*4+1, val, 14, EVs_UIM_GREEN);
    if (val < 318) uim.fillRect(val+1, 16*4+1, 318-val-1, 14, EVs_UIM_BLACK);
}
