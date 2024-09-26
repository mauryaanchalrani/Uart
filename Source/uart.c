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

    UART5_IM_R |= UART_IM_RXIM; // Enable receive interrupt
    NVIC_EN2_R |= (1 << (INT_UART5 - 16));

}

void IntDefaultHandler(void) {
    // Check if the interrupt is caused by receiving data (RX interrupt)
    if (UART5_MIS_R & UART_MIS_RXMIS) {
        // Clear the interrupt flag for receive
        UART5_ICR_R |= UART_ICR_RXIC;

        // Read the received data from the data register
        char receivedData = UART5_DR_R & 0xFF;  // Mask to get the lowest 8 bits (data)

        // Your code to handle the received data
        // For demonstration, toggle a GPIO pin to show data was received
        toggleGPIO(PORTE, PIN1);

        // Optionally, you can process the received data here
        // Example: Print received data over UART (echo back)
        UART5_SendChar(receivedData);
    }
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








