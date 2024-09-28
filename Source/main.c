#include <stdint.h>
#include <stdbool.h>
#include "inc/TM4C1233E6PZ.h"
#include "GPIO.h"
#include "TIMER.h"
#include "common.h"
#include "schedular.h"
#include "driverlib/interrupt.h"
#include "uart.h"
#include "driverlib/sysctl.h"
#include "e2p.h"



schedular_flg_t schedular_flg;

int main(void)
 {
    Timer0_Init();
    setGPIO_Direction(PORTE,PIN1,OUTPUT);
    //setGPIO_Direction(PORTE,PIN5,OUTPUT);
    //setGPIO_Direction(PORTE,PIN0,OUTPUT);
    //setGPIO_Direction(PORTE,PIN1,OUTPUT);


   // SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    UART5_Init();
        SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
        EEPROM_Init();

             //Wait until the EEPROM module is ready
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)) {}

            //SPI_Init();
            //SPI_Write(0x55);                // Send 0x55 via SPI
            //uint8_t receivedData = SPI_Read();

    writeGPIO(PORTE,PIN1,1);
    EEPROM_Write(0x00,25);
    IntMasterEnable();
     __asm(" CPSIE I");      // enable
    //__asm(" CPSID I");    // disable
    while(1)
    {

        //toggleGPIO(PORTF,PIN4);
        //writeGPIO(PORTH,PIN1,1);

        if(schedular_flg.flg_10ms==true)
        {
            schedular_flg.flg_10ms=false;
           // UART5_SendString("Wi-fi Connecting..\n");
            //toggleGPIO(PORTE,PIN4);
        }
        if(schedular_flg.flg_50ms==true)
        {
            schedular_flg.flg_50ms=false;
           // toggleGPIO(PORTE,PIN0);
            //UART5_SendString("Hello..\n");
        }
        if(schedular_flg.flg_100ms==true)
        {
            schedular_flg.flg_100ms=false;
           // UART5_SendString("Anchal...\n");
            //toggleGPIO(PORTE,PIN1);
        }
        if(schedular_flg.flg_1sec==true)
        {

            schedular_flg.flg_1sec=false;
            UART5_SendString("\nData Successfully Execute");

            uint32_t readData=25;  // = EEPROM_Read(0x00);
            UART5_SendString("\nRead Data :");

            readData = EEPROM_EERDWR_R;
            UWriteInt(readData & 0xFF);
           // UWriteBytes((char*)readData,sizeof(readData));
           // toggleGPIO(PORTE,PIN4);
        }


    }
}

void delay_ms(uint32_t delay)
{
    uint32_t i;
    uint32_t cycles = (SYSTEM_CLOCK_HZ / 3000) * delay;  // Approximate loop cycles for 1 ms delay

    for (i = 0; i < cycles; i++) {
        // Empty loop to create delay
        __asm(" NOP");
    }
}



