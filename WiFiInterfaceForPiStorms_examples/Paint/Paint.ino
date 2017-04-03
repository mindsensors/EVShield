#include <EVShield.h>
#include <EVs_UIModule.h>

EVShield ev = EVShield();
EVs_UIModule uim = EVs_UIModule();

void setup() {
  ev.init();
  uim.begin();
  uim.clearScreen();
}

void loop() {
  uint16_t x, y;
  ev.getTouchscreenValues(&x, &y);
  uim.drawPixel(x, y, EVs_UIM_WHITE);
}
