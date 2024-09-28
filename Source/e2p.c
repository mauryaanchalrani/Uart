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

void EEPROM_Init(void) {
    // Enable the clock to the EEPROM module
    SYSCTL_RCGCEEPROM_R = 0x01;

    // Wait for the EEPROM to be ready
    while ((SYSCTL_PREEPROM_R & 0x01) == 0) {}

    // Perform a mass erase of the EEPROM
    EEPROM_EESIZE_R |= (1 << 31); // EERASE bit

    // Wait for the erase to complete
    while (EEPROM_EEDONE_R & 0x01) {}
}

void EEPROM_Write(uint32_t ui32Address, uint32_t ui32Data) {
    // Wait until EEPROM is ready
    while (EEPROM_EEDONE_R & 0x01) {}

    // Set the block and offset address
    EEPROM_EEBLOCK_R = ui32Address >> 6;
    EEPROM_EEOFFSET_R = (ui32Address >> 2) & 0xF;

    // Write the data to the EEPROM
    EEPROM_EERDWR_R = ui32Data;

    // Wait for the write operation to complete
    while (EEPROM_EEDONE_R & 0x01) {}
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
