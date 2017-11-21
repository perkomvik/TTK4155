/*
 * Pong.c
 *
 * Created: 18.11.2017 11:58:59
 *  Author: mariuesk
 */ 
#include "pong.h"

void pong_play(game_mode mode){
	switch(mode){
		case(JOY):
			pong_JOY();
			break;
		case(SLIDER):
			pong_slider();
			break;
		default:
			break;
	}
}

void pong_JOY(void){
	uint8_t game_over = 0;
	CAN_message instructions;
	CAN_message results;
	results.id = PONG_RESULT;
	results.length = 2;
	results.data[GAME_OVER] = 0;
	results.data[GOAL] = 0;
	
	IR_calibrate();
	
	//Start flow of information
	CAN_message_send(&results);
	
	while(!game_over){
		IR_MM();
		results.data[GOAL] = is_goal();
		if(CAN_receive(&instructions)){
			motor_set_speed(instructions.data[JOY_X]);
			//set_servo(instructions.data[JOY_Y]);
			set_servo(127);
			solenoid_fire(instructions.data[JOY_B]);
			_delay_ms(10); // Needed for solenoid disturbance
			CAN_message_send(&results);
		}
		
		game_over = is_game_over();
	}
	results.data[GAME_OVER] = game_over;
	motor_set_speed(STOP);
	CAN_message_send(&results);
}



void pong_slider(void){
	uint8_t game_over = 0;
	CAN_message instructions;
	CAN_message results;
	results.id = PONG_RESULT;
	results.length = 2;
	results.data[GAME_OVER] = 0;
	results.data[GOAL] = 0;

	
	PID_calibrate();
	IR_calibrate();
	
	//Start flow of information
	CAN_message_send(&results);
	
	while(!game_over){
		IR_MM();
		results.data[GOAL] = is_goal();
		if(CAN_receive(&instructions)){
			PID(instructions.data[SLIDER]);
			set_servo(instructions.data[JOY_X]);
			solenoid_fire(instructions.data[JOY_B]);
			_delay_ms(10); // Needed for solenoid disturbance
			CAN_message_send(&results);
		}
		game_over = is_game_over();
	}
	
	results.data[GAME_OVER] = game_over;
	motor_set_speed(STOP);
	CAN_message_send(&results);
}

