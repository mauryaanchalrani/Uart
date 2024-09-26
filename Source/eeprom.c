/*
 * eeprom.c
 *
 *  Created on: 09-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/TM4C1233E6PZ.h"
#include "GPIO.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"
#include "driverlib/debug.h"
#include "uart.h"
#include "eeprom.h"


void init_e2p(void) {

    // Initialize EEPROM
     if(EEPROMInit() != EEPROM_INIT_OK) {
        // Error initializing EEPROM
        UART5_SendString("EEPROM Initialization Failed\n");
        while(1);
    }

    // Data to write (a single 32-bit word)
    uint32_t data = 0x12345678;

    // EEPROM memory address to write the data
    uint32_t address = 0x0;  // Starting at EEPROM address 0

    // Byte count (4 bytes for a 32-bit word)
    uint32_t byteCount = sizeof(data);

    // Write data to EEPROM
    EEPROMProgram(&data, address, byteCount);

    // Read back data to verify
//    uint32_t dataRead;

//     EEPROMRead(&dataRead, address, byteCount);
//
//
//     //Check if the data matches
//      if (dataRead == data) {
//        // Data was written and read correctly
//       UART5_SendString("Data written and verified successfully\n");
//
//      }
//      else {
//        // Error: Data mismatch
//        UART5_SendString("Error: Data mismatch\n");
//      }

    while(1){  // Infinite loop to end program
    uint32_t dataRead;
    EEPROMRead(&dataRead, address, byteCount);


         //Check if the data matches
          if (dataRead == data) {
            // Data was written and read correctly
           UART5_SendString("Data written and verified successfully\n");

          }
          else {
            // Error: Data mismatch
            UART5_SendString("Error: Data mismatch\n");
          }
    }
}




