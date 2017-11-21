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
void PID_calibrate(void){
	motor_set_direction(21);
	motor_set_speed(50);
	int16_t cur_rot = motor_read_rotation(0);
	int16_t prev_rot = cur_rot+200;
	while(prev_rot != cur_rot) {
		printf("Encoder prev: %d\t",prev_rot);
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_read_rotation(0);
		
		printf("Encoder cur: %d\n",prev_rot);
	}
	
	motor_set_speed(0);
	_delay_us(500);
	motor_reset_encoder();
	motor_set_direction(150);
	motor_set_speed(200);
	cur_rot = 0;
	prev_rot = cur_rot-200;
	while(prev_rot != cur_rot) {
		printf("Encoder prev: %d\n",prev_rot);
		prev_rot = cur_rot;
		_delay_ms(40);
		cur_rot = motor_read_rotation(0);
		
		//printf("Encoder cur: %d\n",prev_rot);
	}
	rot_max = cur_rot;
}
void PID(uint8_t pos_ref){
	if (timer_flag){
		clear_bit(TIMSK2,TOIE2); //disbale interupt whiole handling PID 
		int16_t motor_rot = motor_read_rotation(0);
		//printf("Encoder: %d\t", motor_rot);
		double measured = (double)((motor_rot - rot_min)/(double)(rot_max))*255;
		//printf("Malt: %d\t", (uint16_t)measured);
		//double measured = (motor_rot + motor_middle) / (-motor_middle/100);
		//(double)((read_value - enc_min)/(double)(enc_max))*255;
		
		if(pos_ref >240){
			pos_ref = 240;
			} else if(pos_ref<10){
			pos_ref = 10;
		}
		
	
	
		int16_t error = pos_ref - (int)measured;
		//printf("Error: %d\t", error);
		integral = integral + error * dt;
		int measure = (integral*(Ki));
		//printf("integral: %d\n", measure);
		if (error < 1 && error > -1){
			integral = 0;
		}
	
		double derivative = (error - prev_error)/dt;
	
		int16_t power_signed = 0;
		uint8_t power = 0;
		power_signed = error*Kp + integral*Ki + derivative*Kd;
	
		prev_error = error;
		//printf("power Signed: %d\n",power_signed);
		if (power_signed < 0){
			motor_set_direction(23);
			power = -power_signed;
		}
		else{
			motor_set_direction(140);
				power = power_signed;
		}
	//printf("True power: %d\n", power);
		motor_set_speed_2(power);
		timer_flag = 0;
		set_bit(TIMSK2,TOIE2); //enable interupot
	}
}
void PID_init(void){

	cli(); // Disable global interrupts

	TIMSK2=(1<<TOIE2); // enable timer overflow interrupt for Timer2
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); // start timer2 with /1024 prescaler
	
	sei(); // Enable global interrupts
}
