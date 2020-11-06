#include "lcd.h"
#include "keypad.h"
#include "systick.h"
#include "PORTF.h"
#include "countdown_timer.h"

int main(){
start:
  unsigned char key;
  int sec=0, i=0;
  
  LCD_init();
  keypad_init();
  PORTF_init();
 
  LCD_command(0x80);   //Force cursor to beginning ( 1st line)

  while(1){
	//get time
	gettime(&key, &i, &sec);
	//function to erase
	erase(key, &i, &sec);
	//to check if left switch is pressed
	if(start(i))
	  break;
  }
  //countdown timer function
  if(timer(key, i, sec)==1)
	//if right switch is pressed reset
	goto start;
  //redlight and time's up blinks
  redlightn_timeup(5);
  timeup();
  //reset
  while((GPIO_PORTF_DATA_R & Right_SW) != 0x00){}
  goto start;
  return 0;
}
