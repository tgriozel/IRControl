#include "IR.h"
#include "Buttons.h"

void setup() {
    ir_setup();
    buttons_setup();
}

void loop() {
    if (is_b1_pushed() || is_b2_pushed()) {
        ir_loop();
        Serial.println("Button push recorded");
    }
}
