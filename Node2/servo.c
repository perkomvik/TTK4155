/*
 * servo.c
 *
 * Created: 29.10.2017 12:39:17
 *  Author: mariuesk
 */ 
#include "servo.h"

void servo_init(uint32_t clock_freq){
	float period = 0.02;
	float initial_pos = 0.0015;
	PWM_init(period,clock_freq);
	PWM_pulse_set(initial_pos);
}

void set_servo(uint8_t servo_dir){
	//Servo has slight offset
	if(servo_dir-37 >= 0){
		servo_dir -= 37;
	}

	float min_pw = 0.00095;
	float max_pw = 0.00205;
	
	
	float dir = (float)servo_dir;
	float servo_pw = dir/211666.7 + 0.0009;

	//Saturation
	if (servo_pw < min_pw) {
		servo_pw = min_pw;
	}
	if (servo_pw > max_pw) {
		servo_pw = max_pw;
	}
	
	PWM_pulse_set(servo_pw);

}