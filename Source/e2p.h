/*
 * e2p.h
 *
 *  Created on: 27-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#ifndef SOURCE_E2P_H_
#define SOURCE_E2P_H_



void init_e2p(void);

#define SYSCTL_RCGCEEPROM_R    (*((volatile uint32_t *)0x400FE658))  // Run mode clock gating control
#define EEPROM_EESUPP_R        (*((volatile uint32_t *)0x400AF01C))  // support control and status
#define EEPROM_EEDONE_R        (*((volatile uint32_t *)0x400AF018))  // eeprom done status
#define EEPROM_EEBLOCK_R       (*((volatile uint32_t *)0x400AF004))  // Current block
#define EEPROM_EEOFFSET_R      (*((volatile uint32_t *)0x400AF008))  // Current offset
#define EEPROM_EERDWR_R        (*((volatile uint32_t *)0x400AF010))  // Read-Write
#define EEPROM_EESIZE_R        (*((volatile uint32_t *)0x400AF000))  // Size information
#define EEPROM_EERDWRINC_R     (*((volatile uint32_t *)0x400AF014))  // Read-Write with increment
#define EEPROM_EEUNLOCK_R      (*((volatile uint32_t *)0x400AF020))  // For eeprom Unlock
#define EEPROM_EEPROT_R        (*((volatile uint32_t *)0x400AF030))  // For protection


#define SYSCTL_RCGC_EEPROM     0x1      // Enable EEPROM module
#define EEPROM_DONE_WORKING    0x0      // EEPROM is ready for

typedef struct
{
    int date;
    int month;
    int year;
    int time;
    int hours;
    int minutes;
}myData_t;


uint32_t EEPROM_Read(uint32_t ui32Address);

void EEPROM_Write(uint32_t ui32Address, uint8_t *ui8Data, uint32_t ui32size); //void EEPROM0_Write(uint32_t ui32Address, uint32_t ui32Data);

void EEPROM_Init(void);

#endif /* SOURCE_E2P_H_ */
