/*
 * e2p.c
 *
 *  Created on: 27-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "inc\TM4C1233E6PZ.h"
#include "GPIO.h"
#include "uart.h"
#include "e2p.h"
#include "driverlib/eeprom.h"

myData_t myData;

void EEPROM_Init(void) {

  volatile myData_t dummy;
    dummy.date    = 03;
    dummy.month   = 10;
    dummy.year    = 2024;
    dummy.time    = 1225;
    dummy.hours   = 12 ;
    dummy.minutes = 25 ;

    // Enable the clock to the EEPROM module
    SYSCTL_RCGCEEPROM_R = 0x01;

    // Wait for the EEPROM to be ready
    while ((SYSCTL_PREEPROM_R & 0x01) == 0) {}

    // Perform a mass erase of the EEPROM
    EEPROM_EESIZE_R |= (1 << 31);  // EERASE bit

    // Wait for the erase to complete
    while (EEPROM_EEDONE_R & 0x01) {}
}

//**********************************************
//void EEPROM_Write(uint32_t ui32Address, uint32_t ui32Data) {
//
//    // Wait until EEPROM is ready
//    while (EEPROM_EEDONE_R & 0x01) {}
//
//    // Set the block and offset address
//    EEPROM_EEBLOCK_R = ui32Address >> 6;
//    EEPROM_EEOFFSET_R = (ui32Address >> 2) & 0xF;
//
//
//    // Write the data to the EEPROM
//    EEPROM_EERDWR_R = ui32Data;
//
//    // Wait for the write operation to complete
//    while (EEPROM_EEDONE_R & 0x01) {}
//}
void EEPROM_Write(uint32_t ui32Address, uint8_t *ui8data, uint32_t ui32size)
{
    uint32_t word, i;
    uint8_t data[] = {0x12, 0x34, 0x56};
    uint32_t size = sizeof(data);  // If you're using data, ensure size is calculated based on the actual data.

       for (i = 0; i < ui32size; i += 4)
       {

           while (EEPROM_EEDONE_R & 0x01) {}

               // Set the block and offset address
               EEPROM_EEBLOCK_R = ui32Address >> 6;
               EEPROM_EEOFFSET_R = (ui32Address >> 2) & 0xF;

               word = 0;
                       word |= (i < size)     ? data[i]     : 0;
                       word |= (i + 1 < size) ? (data[i + 1] << 8)  : 0;
                       word |= (i + 2 < size) ? (data[i + 2] << 16) : 0;
                       word |= (i + 3 < size) ? (data[i + 3] << 24) : 0;

                       EEPROM_EERDWR_R = word;

                       ui32Address += 4;
                       while (EEPROM_EEDONE_R & 0x01) {}
       }
}



uint32_t EEPROM_Read(uint32_t ui32Address) {
    // Wait until EEPROM is ready
    while (EEPROM_EEDONE_R & 0x01) {}

    // Set the block and offset address
    EEPROM_EEBLOCK_R = ui32Address >> 6;
    EEPROM_EEOFFSET_R = (ui32Address >> 2) & 0xF;

    // Read and return the data
    return EEPROM_EERDWR_R;
}
