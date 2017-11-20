/*
 * PID.c
 *
 * Created: 16.11.2017 13:27:04
 *  Author: mariuesk
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Utilities.h"

#include "PID.h"
#include "motor.h"

int16_t rot_max = -8800;
int16_t rot_min = 0;

int16_t ref_position = 0;
//double motor_middle = 0;
double Kp = 1;
double Ki = 0.5;
double Kd = 0.03;
double integral = 0;
int16_t prev_error = 0;
double dt = 0.016;

ISR(TIMER2_OVF_vect){
	timer_flag = 1;
}

void PID(void){
	if (timer_flag){
		clear_bit(TIMSK2,TOIE2);
		int16_t motor_rot = motor_read_rotation(0);
		//printf("Encoder: %d\t", motor_rot);
		double measured = (double)((motor_rot - rot_min)/(double)(rot_max))*255;
		//printf("Malt: %d\t", (uint16_t)measured);
		//double measured = (motor_rot + motor_middle) / (-motor_middle/100);
		//(double)((read_value - enc_min)/(double)(enc_max))*255;
		int16_t ref = ref_position;
		if(ref >240){
			ref = 240;
		} else if(ref<10){
			ref = 10;
		}
		
	
	
		int16_t error = ref - (int)measured;
		integral = integral + error * dt;
		//printf("Error: %d\t", error);
		if (error < 1){
			integral = 0;
		}
	
		double derivative = (error - prev_error)/dt;
	
		int16_t power_signed = 0;
		uint8_t power = 0;
		power_signed = Kp * error + Ki  * integral + Kd * derivative;
	
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
	}
	timer_flag = 0;
	set_bit(TIMSK2,TOIE2);
}
void PID_init(){
	
	//-------------INITIALIZE TIMER INPUT-----------------
	
	// Disable global interrupts
	cli();
	
	// enable timer overflow interrupt for Timer2
	TIMSK2=(1<<TOIE2);
	
	// start timer2 with /1024 prescaler
	
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22);
	
	// Enable global interrupts
	sei();
	
	//---------------------------------------------------
	
}

void PID_update_pos_ref(int16_t pos){
	ref_position = pos;
}

void PID_update(difficulty_t difficulty){
	
	switch (difficulty){
		case EASY:
		Kp = 1;
		Ki = 0.5;
		Kd = 0.015;
		break;
		case MEDIUM:
		Kp = 2;
		Ki = 4;
		Kd = 0.1;
		break;
		case HARD:
		Kp = 2;
		Ki = 4;
		Kd = 0.01;
		break;
	}
}