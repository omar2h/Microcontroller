#include "systick.h"
#include "lcd.h"

void systick_delayS(int sec){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_RELOAD_R = 16000000-1;
	NVIC_ST_CTRL_R = 0x5;
	
	for(int i=0;i<sec;i++){
	  while((NVIC_ST_CTRL_R & 0x10000)==0){}
	}
}

void systick_delayMs(int sec){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R =0;
	NVIC_ST_RELOAD_R = 16000-1;
	NVIC_ST_CTRL_R = 0x5;
	
	for(int i=sec;i>0;i--){
	  while((NVIC_ST_CTRL_R & 0x10000)==0){}
	}
}