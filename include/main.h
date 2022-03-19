#ifndef MAIN_H
#define MAIN_H

#include "mbed.h"
#include "rtos.h"
#include "pinDef.h"
#include "RS485/RS485.h"
#include "RS485/RS485_definition.h"

#define nb_motor 8
#define neutralDuty 1500
#define mMax 1900
#define mMin 1100
#define period 20000 // 20000us for Afro30A and 2000us for Emax Bullet 30A

#define PWM_OFFSET 30   // This is offset is needed with the Afro30A. The neutral was at 1470us instead of 1500us.
                        // Also, tested with 1600us. The output was 1570us without the offset.

DigitalIn Killswitch(KILLSWITCH);

RS485 rs(SLAVE_ESC);
PwmOut pwm[8] = {PwmOut (PWM_1), PwmOut (PWM_2), PwmOut (PWM_3), PwmOut (PWM_4), 
  PwmOut (PWM_5), PwmOut (PWM_6), PwmOut (PWM_7), PwmOut (PWM_8)};
Thread threadpwm;

#endif