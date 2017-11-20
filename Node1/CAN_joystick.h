/*
 * CAN_joystick.h
 *
 * Created: 25.10.2017 16:53:03
 *  Author: mariuesk
 */ 


#ifndef CAN_JOYSTICK_H_
#define CAN_JOYSTICK_H_

#include "Utilities.h"
#include "joystick.h"
#include "CAN.h"
void send_joystick_dir(int msg_id);
void send_all_slider(int msg_id);
void send_all_joy(int msg_id);

#endif 