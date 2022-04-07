#include "IR.h"
#include "Buttons.h"

void setup() {
    Serial.begin(115200);
    ir_setup();
    buttons_setup();
}

void loop() {
    if (is_b1_pushed()) {
        Serial.println("Toggling command..");
        ir_command_toggle();
    }
    if (is_b2_pushed()) {
        Serial.println("Sending IR signal..");
        ir_send();
    }
}
