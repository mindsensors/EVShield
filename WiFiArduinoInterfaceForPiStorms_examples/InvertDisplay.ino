#include <EVShield.h>
#include <EVs_UIModule.h>

void setup2() {
    uim.println("Set inverted example");
    uim.println("Tap the left side of the screen for normal colors, or the right side to invert.");
}

void loop2() {
    // reset to browser when GO is pressed
    if (ev.getButtonState(BTN_GO)) ESP.reset();
    
    if (ev.checkButton(  0, 0, 160, 240)) uim.invertDisplay(false);
    if (ev.checkButton(160, 0, 160, 240)) uim.invertDisplay(true);
}
