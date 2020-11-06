#include "tm4c123gh6pm.h"

#define PORTA_MASK		 0X01  //bit 1 mask
#define PORTC_MASK		 0X04  //bit 3 mask

void keypad_init(void);
unsigned char keypad_getkey(void);
void delayMs(int n);
void delayUs(int n);





