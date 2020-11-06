#include "sev_segment.h"

void sev_segment_init(void){
	int dummy;
    dummy = SYSCTL_RCGCGPIO_R;
    SYSCTL_RCGCGPIO_R |= PORTB_MASK;
	SYSCTL_RCGCGPIO_R |= PORTF_MASK;
	GPIO_PORTF_LOCK_R = 0x4c4f434b;
    GPIO_PORTF_CR_R = 0x01f;
	GPIO_PORTB_CR_R = 0x7F;
    GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_DEN_R |= 0xff;
    GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
    GPIO_PORTF_PUR_R |= 0x11;
}

void sev_segment_data(unsigned char key){
	switch(key){
		case '0':
			GPIO_PORTB_DATA_R = n0;
			break;
		case '1':
			GPIO_PORTB_DATA_R = n1;
			break;
		case '2':
			GPIO_PORTB_DATA_R = n2;
			break;
		case '3':
			GPIO_PORTB_DATA_R = n3;
			break;
		case '4':
			GPIO_PORTB_DATA_R = n4;
			break;
		case '5':
			GPIO_PORTB_DATA_R = n5;
			break;
		case '6':
			GPIO_PORTB_DATA_R = n6;
			break;
		case '7':
			GPIO_PORTB_DATA_R = n7;
			break;
		case '8':
			GPIO_PORTB_DATA_R = n8;
			break;
		case '9':
			GPIO_PORTB_DATA_R = n9;
			break;
		case 'A':
			GPIO_PORTB_DATA_R = n10;
			break;
		case 'B':
			GPIO_PORTB_DATA_R = n11;
			break;
		case 'C':
			GPIO_PORTB_DATA_R = n12;
			break;
		case 'D':
			GPIO_PORTB_DATA_R = n13;
			break;
		case '*':
			GPIO_PORTB_DATA_R = n14;
			break;
		case '#':
			GPIO_PORTB_DATA_R = n15;
			break;		  
	}
}