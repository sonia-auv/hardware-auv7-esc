/***
 *
 * Example code: This code is a simple program that turn on/off a LED with a button while another LED flash.
 *
 ***/

#include "main.h"
#include "Utility/utility.h"

void function_pwm ()
{
  uint8_t cmd_array[1] = {CMD_PWM};
  uint8_t buffer_receiver_pwm[255];
  uint8_t nb_commands = 1;
  
  uint16_t data_pwm_1, data_pwm_2;

  while(1)
  {
    if (rs.read(cmd_array,nb_commands,buffer_receiver_pwm) == (nb_motor * 2) && Killswitch == 0)
    {
      for(uint8_t i=0; i<nb_motor; ++i)
      {
        data_pwm_1 = buffer_receiver_pwm[(2*i)+1];
        data_pwm_2 = buffer_receiver_pwm[2*i]*256;
        pwm[i].pulsewidth_us(data_pwm_1+data_pwm_2 + PWM_OFFSET);
      }
    }
  }
}

int main()
{
  for (uint8_t i =0; i<nb_motor; ++i)
  {
    pwm[i].period_us(period);
    pwm[i].pulsewidth_us(neutralDuty + PWM_OFFSET);
  }

  threadpwm.start(function_pwm);
  threadpwm.set_priority(osPriorityHigh);

  thread_isAlive.start(callback(isAliveThread, &rs));
  thread_isAlive.set_priority(osPriorityHigh);
}