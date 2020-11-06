#include "PORTF.h"

void PORTF_init(void){
    SYSCTL_RCGCGPIO_R |= PORTF_MASK; // portf clock enable 0010 0000
    GPIO_PORTF_LOCK_R = 0x4c4f434b;
    GPIO_PORTF_CR_R = 0x01f;
    GPIO_PORTF_DEN_R |= 0x1f; // RED|BLUE|GREEN|Left_SW|Right_SW;
    GPIO_PORTF_DIR_R |= 0x0e;
    GPIO_PORTF_DIR_R &= ~0x11;
    GPIO_PORTF_PUR_R |= (Left_SW|Right_SW);
}