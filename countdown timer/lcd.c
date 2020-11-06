#include "tm4c123gh6pm.h"
#include "lcd.h"


void LCD_init(void){
	SYSCTL_RCGCGPIO_R |= PORTA_MASK; /* enable clock A */
	SYSCTL_RCGCGPIO_R |= PORTB_MASK; /* enable clock B */
	SYSCTL_RCGCGPIO_R |= PORTF_MASK;  // enable clock F
	
	GPIO_PORTA_DIR_R |= 0xE0; /* set PORTA pin 7-5 as output for control */
	GPIO_PORTA_DEN_R |= 0xE0; /* set PORTA pin 7-5 as digital pins */

	GPIO_PORTB_DIR_R = 0xFF; /* all PORTB pins as output */
	GPIO_PORTB_DEN_R = 0xFF; /* all PORTB pins as digital pins */
	
	delayMs(20); /* initialization sequence */
	LCD_command(0x30);
	delayMs(5);
	LCD_command(0x30);
	delayUs(100);
	LCD_command(0x30);
	LCD_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
	LCD_command(0x06); /* move cursor right */
	LCD_command(0x01); /* clear screen, move cursor to home */
	LCD_command(0x0F); /* turn on display, cursor blinking */
}

void LCD_command(unsigned char command){
	GPIO_PORTA_DATA_R = 0; /* RS = 0, R/W = 0  ctrl*/ 
	GPIO_PORTB_DATA_R = command; /* data */
	GPIO_PORTA_DATA_R = EN; /* pulse E */
	delayUs(1);
	GPIO_PORTA_DATA_R = 0;
	if (command < 4)
	delayMs(2); /* command 1 and 2 needs up to 1.64ms */
	else
	delayUs(40); /* all others 40 us */
}

void LCD_data(char data){
    GPIO_PORTA_DATA_R = RS;    /* RS = 1, R/W = 0 */
    GPIO_PORTB_DATA_R = data;
    GPIO_PORTA_DATA_R = EN | RS;   /* pulse E */
    delayUs(1);
    GPIO_PORTA_DATA_R = 0;
    delayUs(40); 
}
//void delayMs(int n){
//	int i, j;
//	for(i = 0 ; i < n; i++)
//		for(j = 0; j < 3180; j++){} /* do nothing for 1 ms */
//}
//
//void delayUs(int n){
//	int i, j;
//	for(i = 0 ; i < n; i++)
//		for(j = 0; j < 3; j++){} /* do nothing for 1 us */
//}