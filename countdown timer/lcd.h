#include "tm4c123gh6pm.h"
#include "keypad.h"

#define PORTA_MASK 	0x01 /* BIT1 mask */
#define PORTB_MASK  0x02 /* BIT2 mask */
#define PORTF_MASK  (1U<<5) //BIT5 mask
#define SWITCH2     (1U)    //BIT1 mask
#define SWITCH1     (1U<<4) //BIT4 mask
#define RS 			0x20 /* BIT5 mask */
#define RW 			0x40 /* BIT6 mask */
#define EN 			0x80 /* BIT7 mask */

void LCD_init(void);
void LCD_command(unsigned char command);
void LCD_data(char data);
//void delayMs(int n);
//void delayUs(int n);