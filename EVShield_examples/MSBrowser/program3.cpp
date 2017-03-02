#include "program3.h"

#include <EVShield.h>
#include <EVs_UIModule.h>

void setup3() {
    uim.println("I2C test");
}

void loop3() {
    uim.fillRect(++iteration%320, 30+iteration/320, 1, 1, EVs_UIM_BLUE);
}
