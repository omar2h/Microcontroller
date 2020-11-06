#define PORTB_MASK       0x02
#define PORTF_MASK       (1U<<5)
#define Left_SW          (1U<<4)
#define Right_SW         (1U)

#define n0 	  ~(0x3F)	
#define n1 	  ~(0x06)
#define n2 	  ~(0x5B)
#define n3 	  ~(0x4F)
#define n4 	  ~(0x66)
#define n5 	  ~(0x6D)
#define n6 	  ~(0x7D)
#define n7 	  ~(0x07)
#define n8 	  ~(0x7F)
#define n9 	  ~(0x6F)
#define n10   ~(0x77) 
#define n11   ~(0x7C)
#define n12   ~(0x39)
#define n13   ~(0x5E)
#define n14   ~(0x79)
#define n15   ~(0x71)

void init(void){
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

