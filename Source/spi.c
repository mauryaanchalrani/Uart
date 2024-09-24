/*
 * spi.c
 *
 *  Created on: 16-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc\TM4C1233E6PZ.h"
#include "GPIO.h"
#include "common.h"
#include "timer.h"
#include "spi.h"

void SPI_Init(void)
{
     SYSCTL_RCGCSSI_R  |= (0X01);       // Enable the clock for SSI0
     SYSCTL_RCGCGPIO_R |= (0x01);      // Enable the clock for PORTE

     GPIO_PORTE_AFSEL_R |= 0x3C;      // Enable alternate functions on PE2, PE3, PE4, PE5
     GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | 0x00222200;
     GPIO_PORTE_AMSEL_R |= 0x3C;      // Enable Digital functionality on PE2, PE3, PE4, PE5
     GPIO_PORTE_AMSEL_R &= ~0x3C;    // Disable Analog Functionality on PE2, PE3, PE4, PE5
     SSI0_CR1_R &= ~SSI_CR1_SSE;     // Disable SSI0
     SSI0_CR1_R = 0x00000000;        // Set as master (bit 1 = 0)
     SSI0_CC_R = 0x0;                // Use system clock for SSI
     SSI0_CPSR_R = 0x02;             // Set clock prescaler to 2 (for a fast clock)
     SSI0_CR0_R = 0x0007;            // Set SCR=0, SPH=0, SPO=0, 8-bit data
     SSI0_CR1_R |= SSI_CR1_SSE;      // Enable SSI0
}

void SPI_Write(uint8_t data)
{
   while ((SSI0_SR_R & SSI_SR_TNF) == 0);  // Wait until transmit FIFO is not full
   SSI0_DR_R = data;                      // Use system clock for SSI
}

uint8_t SPI_Read(void) {
    while ((SSI0_SR_R & SSI_SR_RNE) == 0);  // Wait until receive FIFO is not empty
    return SSI0_DR_R;                      // Read received data
}
