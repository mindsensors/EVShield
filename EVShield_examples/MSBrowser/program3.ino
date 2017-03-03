#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_AbsoluteIMU.h>

EVs_AbsoluteIMU imu;

void drawBar(int height, int progress);

void setup3() {
    imu.init(&ev, SH_BAS1);
    
    uim.println(imu.getFirmwareVersion());
    uim.println(imu.getDeviceID());
    uim.println(imu.getVendorID());
    uim.fillRect(0, 16*4, 320, 16, EVs_UIM_WHITE);
    uim.fillRect(0, 16*6, 320, 16, EVs_UIM_WHITE);
    uim.fillRect(0, 16*8, 320, 16, EVs_UIM_WHITE);
}

void loop3() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    accl myaccl;
    imu.readAccelerometer(myaccl);
    
    drawBar(16*4+1, myaccl.tx);
    drawBar(16*6+1, myaccl.ty);
    drawBar(16*8+1, myaccl.tz);
}

void drawBar(int height, int progress) {
    int val = 318 * progress / 256;
    uim.fillRect(1, height, val, 14, EVs_UIM_GREEN);
    uim.fillRect(val+1, height, 318-val, 14, EVs_UIM_BLACK);
}
