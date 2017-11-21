/*
 * Motor.h
 *
 * Created: 08.11.2017 12:18:29
 *  Author: mariuesk
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "utilities.h"
#include "DAC.h"
#include "CAN.h"

typedef enum {LEFT, RIGHT} motor_direction_t;

void motor_init();
void motor_set_direction(motor_direction_t);
void motor_set_speed(uint8_t speed);
void motor_set_speed_2(uint8_t speed);
void motor_move(int16_t rot_diff, uint8_t power);
int16_t motor_read_rotation(uint8_t);
void motor_reset_encoder();
void motor_encoder_test(void);




#endif /* MOTOR_H_ */
