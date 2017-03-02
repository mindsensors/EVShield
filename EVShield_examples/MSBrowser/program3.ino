#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_AbsoluteIMU.h>

#include "MSBrowser.h"

EVs_AbsoluteIMU imu;

void setup3() {
    imu.init(&ev, SH_BAS1);
    
    uim.println(imu.getFirmwareVersion());
    uim.println(imu.getDeviceID());
    uim.println(imu.getVendorID());
}

void loop3() {
    gyro mygyro;
    imu.readGyro(mygyro);
    uim.setCursor(0, 16*4);
    uim.printf("gyro x:%d | y:%d | z:%d", mygyro.gx, mygyro.gy, mygyro.gz);
}
