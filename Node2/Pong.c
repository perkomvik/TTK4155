/*
 * Pong.c
 *
 * Created: 18.11.2017 11:58:59
 *  Author: mariuesk
 */ 
#include "Pong.h"

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
	results.data[0] = 0;
	results.data[1] = 0;
	
	IR_calibrate();
	
	//Start flow of information
	CAN_message_send(&results);
	
	while(!game_over){
		results.data[1] = is_goal();
		if(CAN_receive(&instructions)){
			//CAN_print(&msg);
			motor_set_direction(instructions.data[0]);
			motor_set_speed(instructions.data[0]);
			//set_servo(instructions.data[1]);
			set_servo(127);
			solenoid_fire(instructions.data[2]);
			_delay_ms(10); // Needed for solenoid disturbance
			CAN_message_send(&results);
		}
		
		game_over = is_game_over();
	}
	results.data[0] = game_over;
	CAN_print(&results);
	CAN_message_send(&results);
}



void pong_slider(void){
	uint8_t game_over = 0;
	CAN_message instructions;
	CAN_message results;
	results.id = PONG_RESULT;
	results.length = 2;
	results.data[0] = 0;
	results.data[1] = 0;
	
	motor_calibrate();
	IR_calibrate();
	
	//Start flow of information
	CAN_message_send(&results);
	
	while(!game_over){
		results.data[1] = is_goal();
		if(CAN_receive(&instructions)){
			//CAN_print(&instructions);
			PID_update_pos_ref(instructions.data[1]);
			PID();
			set_servo(instructions.data[1]);
			//printf("results.data[0]: %d\n", results.data[0]);
			set_servo(instructions.data[0]);
			solenoid_fire(instructions.data[2]);
			_delay_ms(10);
			CAN_message_send(&results);
		}
		game_over = is_game_over();
	}
	
	results.data[0] = game_over;
	motor_set_speed(127);
	CAN_print(&results);
	CAN_message_send(&results);
}
////CAN_print(&msg);
//motor_set_direction(msg.data[1]);
//motor_set_speed(msg.data[1]);
////PID_update_pos_ref(msg.data[1]);
////PID();
//////encoder = motor_read_rotation(0);
//////ready.data[1] = encoder;
//////printf("Encoder: %d\n",encoder);
//set_servo(msg.data[0]);
//solenoid_fire(msg.data[2]);
//_delay_ms(10);
//CAN_message_send(&ready);