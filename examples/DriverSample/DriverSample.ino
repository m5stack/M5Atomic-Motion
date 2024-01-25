/**
 * @file DriverSample.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief Atomic Motion Test
 * @version 0.1
 * @date 2024-01-24
 *
 *
 * @Hardwares: M5AtomS3 + Atomic Motion
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5AtomicMotion: https://github.com/m5stack/M5Atomic-Motion
 */

#include "M5Unified.h"
#include "M5GFX.h"
#include "M5AtomicMotion.h"

M5AtomicMotion AtomicMotion;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Display.setTextColor(GREEN);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setTextSize(2);
    M5.Display.drawString("Atomic Init", M5.Display.width() / 2,
                          M5.Display.height() / 2);

    m5::board_t board = M5.getBoard();

    uint8_t sda, scl;

    if (board == m5::board_t::board_M5AtomS3) {
        sda = 38;
        scl = 39;
    } else {
        sda = 25;
        scl = 21;
    }

    while (!AtomicMotion.begin(&Wire, M5_ATOMIC_MOTION_I2C_ADDR, sda, scl,
                               100000)) {
        M5.Display.clear();
        M5.Display.drawString("Init Fail", M5.Display.width() / 2,
                              M5.Display.height() / 2);
        Serial.println("Atomic Motion begin failed");
        delay(1000);
    }

    M5.Display.clear();
    M5.Display.drawString("Motion", M5.Display.width() / 2,
                          M5.Display.height() / 2);

    Serial.println("Atomic Motion Test");
}

void loop() {
    for (int ch = 0; ch < 2; ch++) {
        AtomicMotion.setMotorSpeed(ch, 127);
        Serial.printf("Motor Channel %d: %d \n", ch,
                      AtomicMotion.getMotorSpeed(ch));
    }
    delay(1000);
    for (int ch = 0; ch < 2; ch++) {
        AtomicMotion.setMotorSpeed(ch, -127);
        Serial.printf("Motor Channel %d: %d \n", ch,
                      AtomicMotion.getMotorSpeed(ch));
    }
    delay(1000);
    for (int ch = 0; ch < 2; ch++) {
        AtomicMotion.setMotorSpeed(ch, 0);
        Serial.printf("Motor Channel %d: %d \n", ch,
                      AtomicMotion.getMotorSpeed(ch));
    }
    delay(1000);
    for (int ch = 0; ch < 4; ch++) {
        AtomicMotion.setServoAngle(ch, 180);
        Serial.printf("Servo Channel %d: %d \n", ch,
                      AtomicMotion.getServoAngle(ch));
    }
    delay(1000);
    for (int ch = 0; ch < 4; ch++) {
        AtomicMotion.setServoAngle(ch, 0);
        Serial.printf("Servo Channel %d: %d \n", ch,
                      AtomicMotion.getServoAngle(ch));
    }
    delay(1000);
}
