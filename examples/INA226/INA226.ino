/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include <M5Unified.h>
#include <M5GFX.h>
#include <M5AtomicMotion.h>

M5AtomicMotion AtomicMotion;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);

    M5.Display.setTextColor(GREEN);
    M5.Display.setTextDatum(middle_center);
    M5.Display.setTextSize(2);

    m5::board_t board = M5.getBoard();

    uint8_t sda, scl;

    if (board == m5::board_t::board_M5AtomLite) {
        sda = 25;
        scl = 21;
    } else {
        sda = 38;
        scl = 39;
    }

    while (!AtomicMotion.begin(&Wire, M5_ATOMIC_MOTION_I2C_ADDR, sda, scl,
                               100000)) {
        M5.Display.drawString("Init Fail", M5.Display.width() / 2,
                              M5.Display.height() / 2);
        printf("Atomic Motion begin failed\n");
        delay(1000);
    }

    printf("Atomic Motion Test\n");
    M5.Display.drawString("INA226", M5.Display.width() / 2, 25);
    M5.Display.setTextColor(TFT_YELLOW);
}

void loop() {
    float voltage = AtomicMotion.ina226.readBusVoltage();
    float current = AtomicMotion.ina226.readShuntCurrent();

    printf("voltage: %.2f V\n", voltage);
    printf("current: %.2f A\n", current);

    M5.Display.fillRect(0, 42, M5.Display.width(), M5.Display.height() - 42,
                        TFT_BLACK);
    M5.Display.setCursor(30, 65);
    M5.Display.printf("%.1f V", voltage);
    M5.Display.setCursor(30, 100);
    M5.Display.printf("%.1f A", current);

    delay(1000);
}