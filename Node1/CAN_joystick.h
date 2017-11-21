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

void CAN_send_JOY_dir(uint8_t msg_id);
void CAN_send_all_slider(uint8_t msg_id);
void CAN_send_all_JOY(uint8_t msg_id);

#endif 