/*
 * TL.c
 *
 *  Created on: 05-Sep-2024
 *      Author: ANCHAL MAURYA
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/TM4C1233E6PZ.h"
#include "timer.h"
#include "GPIO.h"
#include "schedular.h"
#include "TL.h"


void Timer1_Init()
{
    uint32_t load_value = (SYSTEM_CLOCK_HZ / 1000) * TIMER0_VALUE - 1;

    SYSCTL_RCGCTIMER_R |= 0x01;  // Enable Timer 0 cLOCK
    TIMER0_CTL_R &= ~0x01;       // Disable Timer 0
    TIMER0_CFG_R =  0x00;         // 32-bit mode
    TIMER0_TAMR_R = 0x02;        // Periodic mode
    TIMER0_TAILR_R = load_value; // Load interval
    TIMER0_ICR_R = 0x01;         // Clear interrupt
    TIMER0_IMR_R = 0x01;         // Enable interrupt
    TIMER0_CTL_R |= 0x01;       // Enable Timer 0

    NVIC_EN0_R |= (1 << 19);    // Enable Timer 0 interrupt in NVIC
}
void Timer1_Handler(void)
{
    static uint8_t state = 0;

        if(state == 0)
        {
            GPIO_PORTE_DATA_R |= (1<<4);
            GPIO_PORTE_DATA_R &= ~(1<<4);
//            state = 1;
//            GPIO_PORTE_DATA_R &= ~(1<<4);
            TIMER0_TAILR_R = 8000000;
        }
        else if(state == 1)
        {
            GPIO_PORTE_DATA_R &= ~(1 << 4); // Turn off pin 4
            GPIO_PORTE_DATA_R |= (1 << 5);  // Turn on pin 5
//                    state = 2;
                    TIMER0_TAILR_R = 2000000;
        }
        else
        {
            GPIO_PORTE_DATA_R = (1<<1);
//            state = 0;
            TIMER0_TAILR_R = 12000000;
        }
    }





