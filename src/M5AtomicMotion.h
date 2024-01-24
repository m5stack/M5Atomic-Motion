#ifndef _M5_ATOMIC_MOTION_H
#define _M5_ATOMIC_MOTION_H

#include <Arduino.h>
#include "I2C_Class.h"

#define M5_ATOMIC_MOTION_I2C_ADDR 0x38

class M5AtomicMotion {
   private:
    uint8_t _addr;
    I2C_Class _i2c;

   public:
    bool begin(TwoWire *_wire = &Wire, uint8_t addr = M5_ATOMIC_MOTION_I2C_ADDR,
               uint8_t sda = 25, uint8_t scl = 21, long freq = 100000);
    uint8_t setServoAngle(uint8_t servo_ch, uint8_t angle);
    uint8_t setServoPulse(uint8_t servo_ch, uint16_t width);
    uint8_t setMotorSpeed(uint8_t motor_ch, int8_t speed);
    uint8_t getServoAngle(uint8_t servo_ch);
    uint16_t getServoPulse(uint8_t servo_ch);
    int8_t getMotorSpeed(uint8_t motor_ch);
};

#endif
