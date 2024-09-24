/*
 * TIMER.h
 *
 *  Created on: 30-Aug-2024
 *      Author: DELL
 */

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

#define PRIMASK_ADDR 0xE000ED04
#define PRIMASK (*((volatile uint32_t *)PRIMASK_ADDR))

#define SYSTEM_CLOCK_HZ 16000000U  // Assuming a 16 MHz system clock
#define TIMER0_VALUE 10                             //in msecs



void Timer0_Init();
void disable_irq(void);
void enable_irq(void);
#endif /* SOURCE_TIMER_H_ */
