/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
#include <M5Unified.h>
#include <M5GFX.h>
#include <M5AtomicMotion.h>

M5AtomicMotion AtomicMotion;

void setup()
{
    auto cfg = M5.config();
    M5.begin(cfg);

    m5::board_t board = M5.getBoard();
    uint8_t sda = 0, scl = 0;

    if (board == m5::board_t::board_M5AtomLite || board == m5::board_t::board_M5AtomMatrix ||
        board == m5::board_t::board_M5AtomEcho) {
        sda = 25;
        scl = 21;
    } else if (board == m5::board_t::board_M5AtomS3 || board == m5::board_t::board_M5AtomS3R ||
               board == m5::board_t::board_M5AtomS3Lite || board == m5::board_t::board_M5AtomS3RExt ||
               board == m5::board_t::board_M5AtomS3RCam) {
        sda = 38;
        scl = 39;
    }

    while (!AtomicMotion.begin(&Wire, M5_ATOMIC_MOTION_I2C_ADDR, sda, scl, 100000)) {
        printf("Atomic Motion begin failed\n");
        delay(1000);
    }

    printf("Atomic Motion INA226 Test\n");
}

void loop()
{
    float voltage = AtomicMotion.ina226.readBusVoltage();
    float current = AtomicMotion.ina226.readShuntCurrent();

    printf("voltage: %.2f V\n", voltage);
    printf("current: %.2f A\n", current);

    delay(1000);
}
