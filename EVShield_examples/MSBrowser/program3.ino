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
    
    gyro mygyro;
    imu.readGyro(mygyro);
    int val = 318 * mygyro.gx / 65536;
    uim.fillRect(1, 16*4+1, val, 14, EVs_UIM_GREEN);
    uim.fillRect(51, 16*4+1, 318-val, 14, EVs_UIM_BLACK);
    uim.fillRect(0, 5*16+1, 90, 16, EVs_UIM_BLACK);
    uim.setCursor(0, 5*16+1);
    uim.println(mygyro.gx);
    
    delay(100);
}
