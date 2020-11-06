#include "tm4c123gh6pm.h"

#define PORTB_MASK       0x02    //bit 2 mask
#define PORTF_MASK       (1U<<5) //bit 5 mask

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

void sev_segment_init(void);
void sev_segment_data(unsigned char key);
