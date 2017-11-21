/*
 * PID.c
 *
 * Created: 16.11.2017 13:27:04
 *  Author: mariuesk
 */ 




#include "PID.h"


ISR(TIMER2_OVF_vect){
	timer_flag = 1;
}

void PID_init(void){

	cli(); // Disable global interrupts

	TIMSK2=(1<<TOIE2); // enable timer overflow interrupt for Timer2
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); // start timer2 with /1024 prescaler
	
	sei(); // Enable global interrupts
}

void PID_calibrate(void){
	motor_set_dir(LEFT);
	motor_set_speed_PID(50);
	int16_t cur_rot = motor_read_rotation();
	int16_t prev_rot = cur_rot+200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_read_rotation();
	}
	
	motor_set_speed(0);
	_delay_us(500);
	motor_reset_encoder();

	motor_set_dir(RIGHT);
	motor_set_speed_PID(50);
	cur_rot = 0;
	prev_rot = cur_rot-200;

	while(prev_rot != cur_rot){
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_read_rotation();
	}
	motor_set_speed(0);
	rot_max = cur_rot;
	
}
void PID(uint8_t pos_ref){
	if (timer_flag){
		clear_bit(TIMSK2,TOIE2); //disable interrupt while handling PID 
		int16_t motor_rot = motor_read_rotation();
		double measured = (double)((motor_rot - rot_min)/(double)(rot_max))*255; //Scale to 0-255 based on calibrated values

		//Saturation of position
		if(pos_ref >240){
			pos_ref = 240;
		} else if(pos_ref<10){
			pos_ref = 10;
		}
		
		int16_t error = pos_ref - (int)measured;
		integral = integral + error * dt;

		//if abs(error) < 1
		if (error < 1 && error > -1){
			integral = 0;
		}
	
		double derivative = (error - prev_error)/dt;
		int16_t speed = 0;
		uint8_t speed_abs = 0;
		speed = error*Kp + integral*Ki + derivative*Kd;
		prev_error = error;

		if (speed < 0){
			motor_set_dir(LEFT);
			speed_abs = -speed;
		}
		else{
			motor_set_dir(RIGHT);
			speed_abs = speed;
		}

		motor_set_speed_PID(speed_abs);
		timer_flag = 0;
		set_bit(TIMSK2,TOIE2); //Enable timer interrupt again 
	}
}
