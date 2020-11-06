#include "tm4c123gh6pm.h"
#include "lcd.h"
#include "PORTF.h"
#include "timer.h"

int main(){
  LCD_init();
  PORTF_init();
  LCD_command(0x80);
  while(1){
	if((GPIO_PORTF_DATA_R & Left_SW) == 0x00)
	   break;
  }
  volatile int v1, p;
  LCD_command(0x0C);
  for(int i=0;i<9;i++){
	LCD_command(0x80);
	LCD_data((i + '0'));
	for(int j=0;j<=9;j++){
	  LCD_command(0x81);
	  LCD_data((j + '0'));
	  if(oneshot(1)==1)
		goto decimal;
	  }
	}
decimal :
  v1=TIMER0_TAR_R;
  LCD_data('.');
  int v2=v1;
  int n=0;
  while(v2>0){
	v2/=10;
	n++;
  }
  int t;
  while(n>0){
	  LCD_command(0x82+n);
	  t=v1%10;
	  v1/=10;
	  LCD_data((t + '0'));
	  n--;
  }  
  int blinks=0;
  while(blinks<5){
	  GPIO_PORTF_DATA_R = 0x2;
	  timer1_delayMs(500);
	  GPIO_PORTF_DATA_R = 0x0;
	  timer1_delayMs(500);
	  blinks++;
  }
  return 0;
}
