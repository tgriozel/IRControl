#include <Arduino.h>

#define IRMP_INPUT_PIN 2
#define IRSND_OUTPUT_PIN 3
#define IRSND_IR_FREQUENCY 38000
#define IRSND_PROTOCOL_NAMES 1
#define IRSND_SUPPORT_KASEIKYO_PROTOCOL 1

#include <irsnd.hpp>

uint8_t power_on[6] = {0x40, 0x04, 0x05, 0x28, 0x3D, 0x10};
uint8_t power_off[6] = {0x40, 0x04, 0x05, 0x28, 0xBD, 0x90};
uint8_t sel_plus[6] = {0x40, 0x04, 0x06, 0x02, 0x98, 0x9C};
uint8_t sel_minus[6] = {0x40, 0x04, 0x06, 0x02, 0x18, 0x1C};
uint8_t vol_plus[6] = {0x40, 0x04, 0x06, 0x02, 0x88, 0x8C};
uint8_t vol_minus[6] = {0x40, 0x04, 0x06, 0x02, 0x08, 0x0C};
uint8_t power[6] = {0x40, 0x04, 0x06, 0x02, 0x00, 0x04};

String all_command_names [] = {"power_on", "power_off", "sel_plus", "sel_minus", "vol_plus", "vol_minus", "power"};
uint8_t * all_commands [] = {power_on, power_off, sel_plus, sel_minus, vol_plus, vol_minus, power};
short current_command_idx = 0;

void ir_setup() {
    irsnd_init();
}

void ir_send() {
    uint8_t repeat = 0x0;
    irsnd_send_raw_kaseikyo_data(all_commands[current_command_idx], repeat);
}

void ir_command_toggle() {
    current_command_idx = (current_command_idx + 1) % (sizeof(all_commands) / sizeof(all_commands[0]));
    Serial.println("New command:" + all_command_names[current_command_idx]);
    delay(300);
}

// This is the code I hacked into "irsnd.hpp", from the IRMP library
// void irsnd_send_raw_kaseikyo_data (uint8_t * data, uint8_t repeat)
// {
//     while (irsnd_busy) {} // Wait for last command to have ended
//     irsnd_protocol = IRMP_KASEIKYO_PROTOCOL;
//     irsnd_repeat = repeat;
//     irsnd_suppress_trailer = FALSE;

//     irsnd_buffer[0] = data[0];
//     irsnd_buffer[1] = data[1];
//     irsnd_buffer[2] = data[2];
//     irsnd_buffer[3] = data[3];
//     irsnd_buffer[4] = data[4];
//     irsnd_buffer[5] = data[5];
//     irsnd_busy = TRUE;

//     storeIRTimer(); // Store current timer state to enable alternately send and receive with the same timer
//     initIRTimerForSend(); // Setup timer and interrupts for sending
//     while (irsnd_busy) {} // Wait for frame and leading space to be sent
// }
