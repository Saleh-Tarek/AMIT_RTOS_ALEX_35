/*
 * TMU_MRTOS_program.c
 *
 *  Created on: Mar 31, 2023
 *      Author: Tarek Saleh
 */

#include "LIBRARIES/std_types.h"
#include "LIBRARIES/error_state.h"
#include "LIBRARIES/system_register.h"

#include "TMU_MRTOS_config.h"
#include "TMU_MRTOS_private.h"

static uint16_t Global_u16CounterCTC=0;
static uint16_t Global_u16NumberEnterISR=0;
TCB_t tasks[MAX_TASKS_NUMBER];



/*
 *	ES_t TMU_enInit(void)
 *  where the timer calculations take place.
 *  for timer 0. we have to calculate the maximum overflow time. = 16.32 msec
 * 	Then max value of the OCR0 is 16
 * 	check if the system tick tike <= 16, or >16
 * 	First initialize timer0 in the normal compare match mode with 1024 prescaler [00001101].
 *
 * */

ES_t TMU_enInit(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	TCCR0= 0x0D;
	/*or
	TCCR0 |= (1<<0);
	TCCR0 &= ~(1<<1);
	TCCR0 |= (1<<2);
	TCCR0 |= (1<<3);
	*/
	/*No we have two cases. TICK_TIME <= 16, TICK_TIME >16*/

#if TICK_TIME <= CTC_MAX_TIME && TICK_TIME >=0
	OCR0 = ((TICK_TIME * F_CPU)/(TIMER_PRESCALER*l000ul));
/*need counter for the ctc and counter for entering the isr,
 * here we know it always be 1 as the ticktime is < 16
*/
	Global_u16NumberEnterISR=1;
	Global_u16CounterCTC=1;
	Local_enuErrorState=ES_OK;

	/*What is the ticktime >16
	 * calculate the greatest common factor*/
#elif TICK_TIME > CTC_MAX_TIME
	uint8_t iterator=0,Local_u8MaxGCF=0;
	for (iterator =1; iterator<= CTC_MAX_TIME; iterator++)
	{
		if(TICK_TIME % iterator ==0)
		{
			Local_u8MaxGCF = iterator;
		}
	}
	/*Timer calculation according to the greatest common factor*/
	OCR0 = ((Local_u8MaxGCF * F_CPU)/(TIMER_PRESCALER*1000ul));
	/*Calculate how many time will enter the ISR*/
	Global_u16NumberEnterISR = (TICK_TIME/Local_u8MaxGCF);
	Global_u16CounterCTC=Global_u16NumberEnterISR;
	Local_enuErrorState=ES_OK;

#else
#error "The entered TICK_TIME is not correct."
#endif
	return (Local_enuErrorState);
}

ES_t TMU_enCreateTask(void(*Copy_pfunTask)(void), uint8_t Copy_u8Priority, uint16_t Copy_u16Periodicity)
{
	ES_t Local_enuErrorState = ES_NOK;
/*Check that pointer is not Null*/
	/*Need an array to contain the structure data, and the array's index will represent the task priority*/
	if(Copy_pfunTask !=NULL)
	{
		tasks[Copy_u8Priority].ptr= Copy_pfunTask;
		tasks[Copy_u8Priority].periodicity= Copy_u16Periodicity;
		tasks[Copy_u8Priority].count= Copy_u16Periodicity-1; /*If the task starts that means it has count-1 to start again*/
	/* Later will add more code*/
		Local_enuErrorState=ES_OK;
	}
	else
	{
		Local_enuErrorState= ES_NULL_POINTER;
	}
	return (Local_enuErrorState);
}

/*Here we need to enable the global interrupt and the timer zero compare match interrup*/

ES_t TMU_enStartSchedular(void)
{
	ES_t Local_enuErrorState = ES_NOK;
	/*TIMER0 CTC Interrupt enable*/
	TIMSK |= (1<<1);
	/*Global Interrupt enable*/
	asm("SEI");
	/*incase the main does not have one*/
	while(1);
	Local_enuErrorState=ES_OK;
	return (Local_enuErrorState);
}

/*ISR code *_- */

void __vector_10(void)__attribute__((signal));
void __vector_10(void)
{
	uint8_t iterator;
	Global_u16CounterCTC--;
	/*if the counter reached 0 it means that it is time to run the task, once we inter the ISR we should
	 * decrease the counter by one. */
	if(Global_u16CounterCTC ==0)
	{
		/*Schedular code will check the priority as the array index*/

		for (iterator=0; iterator < MAX_TASKS_NUMBER; iterator++)
		{
			if(tasks[iterator].count==0 && tasks[iterator].ptr !=NULL)
			{
				tasks[iterator].ptr(); /*Call the task a.k.a [function]*/
				tasks[iterator].count = tasks[iterator].periodicity-1; /*after the task is called we need to decrement the counter by one*/
				/*Need to check if the count reached 0, what is there is no task. pointer is null*/

			}
			else /*if the task count did not reach 0. means the task didnt reach the correct time to start again [periodicity]*/
			{
				tasks[iterator].count --;
			}
		}
		/*Now the task was started, need to return back the ctc counter to the ISR entering counter*/
		Global_u16CounterCTC=Global_u16NumberEnterISR;
	}
}

