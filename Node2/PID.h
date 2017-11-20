/*
 * PID.h
 *
 * Created: 16.11.2017 13:25:48
 *  Author: mariuesk
 */ 


#ifndef PID_H_
#define PID_H_



typedef enum{
	EASY,
	MEDIUM,
	HARD
} difficulty_t;
static volatile uint8_t timer_flag = 0;
void PID_update_pos_ref(int16_t pos);
void PID_init();
void PID_update(difficulty_t);
void PID(void);
ISR(TIMER2_OVF_vect);


#endif /* PID_H_ */