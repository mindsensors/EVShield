#include <EVShield.h>
#include <EVs_UIModule.h>

void setup1() {
    uim.println("Motor test");
    ev.bank_a.motorRunRotations(SH_Motor_1, 
                 SH_Direction_Forward, 
                 SH_Speed_Medium,
                 1, 
                 SH_Completion_Wait_For,
                 SH_Next_Action_BrakeHold);
    uim.println("Done (spun one rotation)");
    ESP.reset();
}

void loop1() {
    if (ev.getButtonState(BTN_GO)) ESP.reset();
}
