/*
 * CAN_joystick.c
 *
 * Created: 25.10.2017 16:52:49
 *  Author: mariuesk
 */ 


#include "CAN_joystick.h"

void CAN_send_JOY_dir(uint8_t msg_id){
	uint8_t x  = JOY_get_x();
	uint8_t y = JOY_get_y();
	CAN_msg msg;
	msg.id = msg_id;
	msg.length = 2;
	msg.data[0] = x;
	msg.data[1] = y;
	CAN_message_send(&msg);
}

void CAN_send_all_slider(uint8_t msg_id){
	uint8_t JOY_x  = JOY_get_x();
	uint8_t right_slider = right_slider_pos();
	uint8_t JOY_B = JOY_get_button();
	CAN_msg msg;
	msg.id = msg_id;
	msg.length = 3;
	msg.data[0] = JOY_x;
	msg.data[1] = right_slider;
	msg.data[2] = JOY_B;
	CAN_message_send(&msg);
}

void CAN_send_all_JOY(uint8_t msg_id){
	uint8_t JOY_x  = JOY_get_x();
	uint8_t JOY_y = JOY_get_y();
	uint8_t JOY_B = JOY_get_button();
	CAN_msg msg;
	msg.id = msg_id;
	msg.length = 3;
	msg.data[0] = JOY_x;
	msg.data[1] = JOY_y;
	msg.data[2] = JOY_B;
	CAN_message_send(&msg);
}