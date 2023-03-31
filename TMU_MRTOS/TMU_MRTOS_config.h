/*
 * TMU_MRTOS_config.h
 *
 *  Created on: Mar 31, 2023
 *      Author: Tarek Saleh
 */

#ifndef TMU_MRTOS_CONFIG_H_
#define TMU_MRTOS_CONFIG_H_

/*
 * System Tick time? 	--------> TICK_TIME
 * Maximum tasks number	--------> MAX_TASKS_NUMBER
 * System frequnce		--------> F_CPU
 * The chosen timer. however Timer zero will be used here. no need o configure it. maybe in larg scale projects.
 *
 * */

#define TICK_TIME					20

#define MAX_TASKS_NUMBER			4

//#define F_CPU						16000000ul

#endif /* TMU_MRTOS_CONFIG_H_ */
