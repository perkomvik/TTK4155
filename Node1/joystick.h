/*
 * joystick.h
 *
 * Created: 13.09.2017 17:17:49
 *  Author: perkom
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "Utilities.h"

void JOY_init();
void JOY_calibrate();
int JOY_get_button();
void JOY_get_pos(int arr[]);
char* JOY_get_dir();
uint8_t JOY_get_pos_x();
uint8_t JOY_get_pos_y();
int JOY_get_dir_x();
int JOY_get_dir_y();
int left_slider_pos();
int right_slider_pos();
int left_button();
int right_button();


#endif /* JOYSTICK_H_ */