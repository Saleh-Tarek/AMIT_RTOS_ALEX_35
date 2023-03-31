/*
 * main.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Tarek Saleh
 */


#include "LIBRARIES/std_types.h"
#include "LIBRARIES/error_state.h"
#include "LIBRARIES/system_register.h"

#include "TMU_MRTOS_interface.h"
/*
 * configure the tasks a.k.a[ functions ]
 * Initialize the TMU.
 * Create the tasks
 * Start the schedular
 *
 * */

void LED1(void);
void LED2(void);
void LED3(void);
void LED4(void);

int main (void)
{
	/*Direction of PORTA*/
	DDRA= 0xff;
	TMU_enInit();
	/*The task periodicity will be multiplied by the ticktime*/
	TMU_enCreateTask(LED1,0,10); /*10*20= 200*/
	TMU_enCreateTask(LED2,1,15);/*15*20= 300*/
	TMU_enCreateTask(LED3,2,20);/*20*20= 400*/
	TMU_enCreateTask(LED4,3,25);/*25*20= 500*/
	TMU_enStartSchedular();
}

/*toggle the led*/
void LED1(void)
{
PORTA^=(1<<1);
}
void LED2(void)
{
	PORTA^=(1<<2);
}
void LED3(void)
{
	PORTA^=(1<<3);
}
void LED4(void)
{
	PORTA^=(1<<4);
}
