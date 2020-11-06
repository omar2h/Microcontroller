#include "timer.h"

void timer1_initSec(int sec){
	SYSCTL_RCGCTIMER_R |= 2; /* enable clock to Timer Block 1 */
	TIMER1_CTL_R = 0; /* disable Timer before initialization */
	TIMER1_CFG_R = 0x04; /* 16-bit option */
	TIMER1_TAMR_R = 0x02; /* periodic mode and down-counter */
	TIMER1_TAILR_R = 64000 - 1; /* TimerA interval load value reg */
	TIMER1_TAPR_R = 250 - 1; /* TimerA Prescaler 16MHz/250=64000Hz */
	TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
	TIMER1_CTL_R |= 0x01; /* enable Timer A after initialization */
  for(int i = 0; i < sec; i++){
	while ((TIMER1_RIS_R & 0x1) == 0) ; /* wait for TimerA timeout flag */
	
	TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
}
}

//void timer1_delaySec(int sec){
//  for(int i = 0; i < sec; i++){
//		while ((TIMER1_RIS_R & 0x1) == 0) ; /* wait for TimerA timeout flag */
//		TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
//  }
//}

void timer1_delayMs(int msec){
	SYSCTL_RCGCTIMER_R |= 2; /* enable clock to Timer Block 1 */
	TIMER1_CTL_R = 0; /* disable Timer before initialization */
	TIMER1_CFG_R = 0x04; /* 16-bit option */
	TIMER1_TAMR_R = 0x02; /* periodic mode and down-counter */
	TIMER1_TAILR_R = 16000 - 1; /* TimerA interval load value reg */
	
	//TIMER1_TAPR_R = 250 - 1; /* TimerA Prescaler 16MHz/250=64000Hz */
	TIMER1_ICR_R = 0x1; /* clear the TimerA timeout flag */
	TIMER1_CTL_R |= 0x01; /* enable Timer A after initialization */
	for(int i = 0; i < msec; i++){
		while ((TIMER1_RIS_R & 0x1) == 0) ; /* wait for TimerA timeout flag */
		TIMER1_ICR_R |= 0x1; /* clear the TimerA timeout flag */
  }
}

  int oneshot(float sec){
	int state =0;
    SYSCTL_RCGCTIMER_R |=       0x01;
    TIMER0_CTL_R          =       0;
    TIMER0_CFG_R        =       0x04;
    TIMER0_TAPR_R = 250 - 1;
    TIMER0_TAMR_R       =       0x01;
    TIMER0_TAILR_R       =       (64000*sec)-1;
    TIMER0_ICR_R        |=      0x01;
    TIMER0_CTL_R        |=      0x01;
    volatile int counter = 0;
      while((TIMER0_RIS_R & 0x01)==0){
	  state = GPIO_PORTF_DATA_R & 0x11;
	  if(state == 0x10)
        return 1;
  }
  return 0;
  }