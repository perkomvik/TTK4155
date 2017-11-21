/*
 * joystick.h
 *
 * Created: 13.09.2017 17:17:49
 *  Author: perkom
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "utilities.h"

typedef enum tag_JOY_dir_y{
	UP = -1,
	MIDDLE = 0,
	DOWN = 1,
	DEADZONE = 2
}JOY_dir_y;

void JOY_init(void);
void JOY_get_pos(int arr[]);
JOY_dir_y JOY_get_dir_y(void);
uint8_t JOY_get_button(void);
uint8_t JOY_get_x(void);
uint8_t JOY_get_y(void);
uint8_t left_slider_pos(void);
uint8_t right_slider_pos(void);
uint8_t left_button(void);
uint8_t right_button(void);


#endif /* JOYSTICK_H_ */