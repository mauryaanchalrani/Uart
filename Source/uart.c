/*
 * uart.c
 *
 *  Created on: 06-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#include  <stdint.h>
#include  <stdbool.h>
#include  "inc/tm4c1233e6pz.h"
#include  "GPIO.h"
#include  "uart.h"
#include  "driverlib/interrupt.h"
#include  "common.h"
#include  "driverlib/sysctl.h"


void UART5_Init(void) {
    // Enable UART5 and GPIOE peripherals
    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R5;   // Enable UART5
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;  // Enable GPIOE for UART5 (PE4, PE5)

    // Wait for peripherals to be ready
    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R5) == 0 || (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0);

    // Configure PE4 and PE5 for UART
    GPIO_PORTE_AFSEL_R |= (1 << 4) | (1 << 5);
    GPIO_PORTE_PCTL_R  = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | (1 << 16) | (1 << 20);
    GPIO_PORTE_DEN_R   |= (1 << 4) | (1 << 5);

    // Disable UART5 for configuration
    UART5_CTL_R &= ~UART_CTL_UARTEN;

    UART5_IBRD_R = 65;
    UART5_FBRD_R = 6;
    // Set the frame: 8 data bits, 1 stop bit, no parity, enable FIFO
    UART5_LCRH_R = UART_LCRH_WLEN_8 | UART_LCRH_FEN;

    // Enable UART5 for TX and RX
    UART5_CTL_R |= UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN;

}
//int i=2;
void UART5_Handler0(void)
{
    toggleGPIO(PORTE, PIN1);
  // GPIO_PORTE_DIR_R |= (1<<1);
    //GPIO_PORTE_DEN_R |= (1<<4);
//    if(i==2)
//    {
//        toggleGPIO(PORTE, PIN4);
//    }
//    else
//    {
//       // UART5_SendString("H..");
//    }

}

// Function to send a character over UART5
void UART5_SendChar(char c) {
    while(UART5_FR_R & UART_FR_TXFF);
    UART5_DR_R = c;
}

// Function to send a string over UART5
void UART5_SendString(const char* str) {
    while(*str) {
        UART5_SendChar(*str);
        str++;
    }
}








