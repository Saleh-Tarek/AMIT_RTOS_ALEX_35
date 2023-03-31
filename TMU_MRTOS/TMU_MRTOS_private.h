/*
 * TMU_MRTOS_private.h
 *
 *  Created on: Mar 31, 2023
 *      Author: Tarek Saleh
 */

#ifndef TMU_MRTOS_PRIVATE_H_
#define TMU_MRTOS_PRIVATE_H_

/*
	 * Will need a pointer to function to point to the called function aka task
	 * task periodicity
	 * task count
	 * next session will add state which indicate for other states of the task [suspend, resume,delete]
	 * */

typedef struct
{
	void (*ptr)(void);
	uint16_t periodicity;
	uint16_t count;
}TCB_t;

#define CTC_MAX_TIME			16
#define TIMER_PRESCALER			1024ul
#endif /* TMU_MRTOS_PRIVATE_H_ */
