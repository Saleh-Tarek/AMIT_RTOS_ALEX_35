/*
 * TMU_MRTOS_interface.h
 *
 *  Created on: Mar 31, 2023
 *      Author: Tarek Saleh
 */

#ifndef TMU_MRTOS_INTERFACE_H_
#define TMU_MRTOS_INTERFACE_H_

ES_t TMU_enInit(void);
ES_t TMU_enCreateTask(void(*Copy_pfunTask)(void), uint8_t Copy_u8Priority, uint16_t Copy_u16Periodicity);
ES_t TMU_enStartSchedular(void);

#endif /* TMU_MRTOS_INTERFACE_H_ */
