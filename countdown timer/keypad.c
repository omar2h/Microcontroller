#include "keypad.h"

void keypad_init(void){
	SYSCTL_RCGCGPIO_R |= PORTC_MASK;
	SYSCTL_RCGCGPIO_R |= PORTE_MASK;
	
	GPIO_PORTE_DIR_R |= 0x0F; 
	GPIO_PORTE_DEN_R |= 0x0F; 
	GPIO_PORTE_ODR_R |= 0x0F;
	
	GPIO_PORTC_DIR_R &= ~0xF0; 
	GPIO_PORTC_DEN_R |= 0xF0; 
	GPIO_PORTC_PUR_R |= 0xF0;
}

unsigned char keypad_kbhit(void){
	int col;
	/* check to see any key pressed */
	GPIO_PORTE_DATA_R = 0; /* enable all rows */
	col = GPIO_PORTC_DATA_R & 0xF0; /* read all columns */
	if (col == 0xF0)
		return 0; /* no key pressed */
	else
		return 1; /* a key is pressed */
}

unsigned char keypad_getkey(void){
    const unsigned char keymap[4][4] = {
	{ '1', '2', '3', 'A'},
	{ '4', '5', '6', 'B'},
	{ '7', '8', '9', 'C'},
	{ '*', '0', '#', 'D'}, };
	int row, col;
	
	while (1){
	GPIO_PORTE_DATA_R = 0;
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col == 0xF0)
	    return 0;
	
	row = 0;
	GPIO_PORTE_DATA_R = 0x0E;
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0)
	    break;
	
	row = 1;
	GPIO_PORTE_DATA_R = 0x0D; /* enable row 1 */
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0)
	    break;
	
	row = 2;
	GPIO_PORTE_DATA_R = 0x0B; /* enable row 2 */
	delayUs(1); /* wait for signal to settle */
	col = GPIO_PORTC_DATA_R & 0xF0;
	if (col != 0xF0) 
	    break;
	
	row = 3;
	GPIO_PORTE_DATA_R = 0x07; /* enable row 3 */
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

unsigned char keypad_getchar(void){
	unsigned char key;
	/* wait until the previous key is released */
	do{
	while(keypad_getkey() != 0);
	delayMs(20); /* wait to debounce */
	}while(keypad_getkey() != 0);
	do{
	key = keypad_getkey();
	delayMs(20); /* wait to debounce */
	}while(keypad_getkey() != key);
	return key;
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