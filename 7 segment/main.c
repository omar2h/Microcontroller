#include "tm4c123gh6pm.h"
#include "init.h"
#include "counter.h"

int main(){
  init();
  unsigned char digitPattern[] = {n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15};
  int state = 0;
  volatile int counter = 0;
  
  while(1){
    state = GPIO_PORTF_DATA_R & 0x11;
    delay(1000000);
    switch(state){
      case 0x11:
      	break;
		
      case 0x01: 
      	counter=decrement(counter, digitPattern);
        break;
		
	  case 0x10:
		counter=increment(counter, digitPattern);
		break;
		
	  case 0x00:
		counter=reset(counter, digitPattern);
		break;
	}
  }
  return 0;
}
