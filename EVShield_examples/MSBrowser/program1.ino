#include <EVShield.h>
#include <EVs_UIModule.h>
#include <EVs_SumoEyes.h>

EVs_SumoEyes sis1; // SumoEYEs

void setup1() {
    uim.println("SumoEyes sensor test");
    sis1.init(&ev, SH_BAS1);
    sis1.setShortRange();
    
    uim.setCursor(0, 2*16);
    uim.print("Sumo Eyes (Range: Short)");
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    SE_Zone obzone = sis1.detectObstacleZone();
    
    uim.clearLine(4);
    uim.clearLine(5);
    uim.setCursor(0, 3*16);
    uim.printf("raw value: %d,\nobzone: %d (%s)", sis1.readRaw(), obzone, sis1.OBZoneToString(obzone) );
}
