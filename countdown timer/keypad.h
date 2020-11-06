#include "tm4c123gh6pm.h"

#define PORTC_MASK		 0X04  //bit 3 mask
#define PORTE_MASK		 0X10  //bit 5 mask

void keypad_init(void);
unsigned char keypad_kbhit(void);
unsigned char keypad_getkey(void);
unsigned char keypad_getchar(void);
void delayMs(int n);
void delayUs(int n);





