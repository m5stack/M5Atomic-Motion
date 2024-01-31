#include "M5AtomicMotion.h"

bool M5AtomicMotion::begin(TwoWire *_wire, uint8_t addr, uint8_t sda,
                           uint8_t scl, long freq) {
    _i2c.begin(_wire, sda, scl, freq);
    _addr = addr;
    return _i2c.exist(_addr);
}

uint8_t M5AtomicMotion::setServoAngle(uint8_t servo_ch, uint8_t angle) {
    uint8_t reg = servo_ch;
    if (reg > 3) return 0;
    _i2c.writeByte(_addr, reg, angle);
    return 0;
}

uint8_t M5AtomicMotion::setServoPulse(uint8_t servo_ch,
                                      uint16_t width)  // 0x10        ->16
{
    uint8_t reg     = 2 * servo_ch + 16;
    uint8_t data[2] = {0};
    data[0]         = (width >> 8);
    data[1]         = (width & 0xFF);
    if (reg % 2 == 1 || reg > 32) return 1;

    _i2c.writeBytes(_addr, reg, data, 2);
    return 0;
}

uint8_t M5AtomicMotion::setMotorSpeed(uint8_t motor_ch,
                                      int8_t speed)  // 0x10 ->16
{
    if (motor_ch > 1) return 1;
    uint8_t reg = motor_ch + 32;
    _i2c.writeByte(_addr, reg, (uint8_t)speed);
    return 0;
}

uint8_t M5AtomicMotion::getServoAngle(uint8_t servo_ch) {
    uint8_t reg = servo_ch;
    return _i2c.readByte(_addr, reg);
}

uint16_t M5AtomicMotion::getServoPulse(uint8_t servo_ch) {
    uint8_t data[2] = {0};
    uint8_t reg     = 2 * servo_ch | 0x10;
    _i2c.readBytes(_addr, reg, data, 2);
    return (data[0] << 8) + data[1];
}

int8_t M5AtomicMotion::getMotorSpeed(uint8_t motor_ch) {
    if (motor_ch > 1) return 1;
    uint8_t reg = motor_ch | 0x20;
    return (int8_t)_i2c.readByte(_addr, reg);
}
