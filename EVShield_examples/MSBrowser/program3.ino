#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_AbsoluteIMU.h>

EVs_AbsoluteIMU imu;

void setup3() {
    imu.init(&ev, SH_BAS1);
    
    uim.println(imu.getFirmwareVersion());
    uim.println(imu.getDeviceID());
    uim.println(imu.getVendorID());
    uim.println();
    uim.println("gyro, accel, magneticField");
}

void loop3() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    gyro mygyro;
    imu.readGyro(mygyro);
    uim.clearLine(6);
    uim.setCursor(0, 16*5);
    uim.printf("x:%d | y:%d | z:%d", mygyro.gx, mygyro.gy, mygyro.gz);
    
    accl myaccl;
    imu.readAccelerometer(myaccl);
    uim.clearLine(7);
    uim.setCursor(0, 16*6);
    uim.printf("x:%d | y:%d | z:%d", myaccl.tx, myaccl.ty, myaccl.tz);
    
    magnetic_field mymgnt;
    imu.readMagneticField(mymgnt);
    uim.clearLine(8);
    uim.setCursor(0, 16*7);
    uim.printf("x:%d | y:%d | z:%d", mymgnt.mx, mymgnt.my, mymgnt.mz);
    
    cmps mycmps;
    imu.readCompass(mycmps);
    uim.clearLine(9);
    uim.clearLine(10);
    uim.setCursor(0, 16*8);
    uim.printf("compass: %d\nerror: %d", mycmps.heading, mycmps.error);
}
