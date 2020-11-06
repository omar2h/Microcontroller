#include "keypad.h"

void keypad_init(void){
    int dummy;
    dummy = SYSCTL_RCGCGPIO_R;
	SYSCTL_RCGCGPIO_R |= PORTA_MASK;
	SYSCTL_RCGCGPIO_R |= PORTC_MASK;
	
	GPIO_PORTA_DIR_R |= 0xF0; 
	GPIO_PORTA_DEN_R |= 0xF0; 
	GPIO_PORTA_ODR_R |= 0xF0; 
	GPIO_PORTC_DIR_R &= ~0xF0; 
	GPIO_PORTC_DEN_R |= 0xF0; 
	GPIO_PORTC_PUR_R |= 0xF0;
}

unsigned char keypad_getkey(void){
    const unsigned char keymap[4][4] = {
	{ '1', '2', '3', 'A'},
	{ '4', '5', '6', 'B'},
	{ '7', '8', '9', 'C'},
	{ '*', '0', '#', 'D'}, };
	int row, col;
	
	while (1){
	GPIO_PORTA_DATA_R = 0;
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col == 0xF0)
	    return 0;
	
	row = 0;
	GPIO_PORTA_DATA_R = 0xE0;
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0)
	    break;
	
	row = 1;
	GPIO_PORTA_DATA_R = 0xD0; /* enable row 1 */
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0)
	    break;
	
	row = 2;
	GPIO_PORTA_DATA_R = 0xB0; /* enable row 2 */
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) 
	    break;
	
	row = 3;
	GPIO_PORTA_DATA_R = 0x70; /* enable row 3 */
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0)
	    break;
	
	return 0; /* if no key is pressed */
	}
	
	if (col == 0xE0)
	    return keymap[row][0]; /* key in column 0 */
	
	if (col == 0xD0)
	    return keymap[row][1]; /* key in column 1 */
	
	if (col == 0xB0)
	    return keymap[row][2]; /* key in column 2 */
	
	if (col == 0x70)
	    return keymap[row][3]; /* key in column 3 */
	
	return 0;
}

void delayMs(int n){
	int i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3180; j++){} /* do nothing for 1 ms */
}

void delayUs(int n){
	int i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3; j++){} /* do nothing for 1 us */
}