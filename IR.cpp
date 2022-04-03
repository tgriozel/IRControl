#include <Arduino.h>
#include <IRremote.hpp>

#define DECODE_NEC
#define DECODE_DISTANCE

#define IR_RECEIVE_PIN 2
#define IR_SEND_PIN 3

void ir_setup()
{
    Serial.begin(115200);
    delay(4000);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    IrSender.begin(IR_SEND_PIN);
}

void send_ir_data() {
    uint16_t address = 0x0528;
    uint8_t command = 0xBD;
    uint_fast8_t numberOfRepeats = 0;
    uint16_t vendorCode = 0x4004;
    IrSender.sendKaseikyo(address, command, numberOfRepeats, vendorCode);
}

void receive_ir_data() {
    if (IrReceiver.decode()) {
        IRData data = IrReceiver.decodedIRData;
        Serial.print(F("Decoded protocol: "));
        Serial.print(getProtocolString(data.protocol));
        Serial.print(F(", decoded raw data: "));
        Serial.print(data.decodedRawData, HEX);
        Serial.print(F(", decoded address: "));
        Serial.print(data.address, HEX);
        Serial.print(F(", decoded command: "));
        Serial.println(data.command, HEX);
        IrReceiver.resume();
    }
}

void ir_loop() {
    send_ir_data();

    // wait for the receiver state machine to detect the end of a protocol
    delay((RECORD_GAP_MICROS / 1000) + 5);
    receive_ir_data();

    delay(100);
}
