/*
 * CAN_joystick.c
 *
 * Created: 25.10.2017 16:52:49
 *  Author: mariuesk
 */ 


#include "CAN_joystick.h"

void send_joystick_dir(int msg_id){
	uint8_t x  = JOY_get_pos_x();
	uint8_t y = JOY_get_pos_y();
	//printf("Joystick X: %d \n", x);
	CAN_message msg;
	msg.id = msg_id;
	msg.length = 2;
	msg.data[0] = x;
	msg.data[1] = y;
	CAN_message_send(&msg);
}

void send_all_slider(int msg_id){
	uint8_t x  = JOY_get_pos_x();
	//uint8_t slider = right_slider_pos();
	uint8_t slider = right_slider_pos();
	uint8_t button = JOY_get_button();
	//printf("X: %d \t slider: %d \t B: %d \n", x,slider,button);
	CAN_message msg;
	msg.id = msg_id;
	msg.length = 3;
	msg.data[0] = x;
	msg.data[1] = slider;
	msg.data[2] = button;
	CAN_message_send(&msg);
}

void send_all_joy(int msg_id){
	uint8_t x  = JOY_get_pos_x();
	//uint8_t slider = right_slider_pos();
	uint8_t y = JOY_get_pos_y();
	uint8_t button = JOY_get_button();
	//printf("X: %d \t Y: %d \t B: %d \n", x,y,button);
	CAN_message msg;
	msg.id = msg_id;
	msg.length = 3;
	msg.data[0] = x;
	msg.data[1] = y;
	msg.data[2] = button;
	CAN_message_send(&msg);
}