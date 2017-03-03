#include <EVShield.h>
#include <EVs_UIModule.h>

void setup2() {
    uim.println("Touchscreen test");
}
void loop2() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    uim.clearLine(3);
    uim.setCursor(0, 32);
    uint16_t x, y;
    ev.getTouchscreenValues(&x, &y);
    uim.printf("x: %u, y:%u", x, y);
    delay(8);
}
