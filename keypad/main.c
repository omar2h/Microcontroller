#include "sev_segment.h"
#include "keypad.h"

int main(){
	sev_segment_init();
	keypad_init();
	unsigned char key;
	
	while(1){
	    do{
			key=keypad_getkey();
			delayMs(2);
		}
		while(keypad_getkey() != 0);
		sev_segment_data(key);
		do{
		    while(keypad_getkey() != 0);
			delayMs(2); 
		}
		while(keypad_getkey() != 0);
	}
  return 0;
}