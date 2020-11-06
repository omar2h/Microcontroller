#include "lcd.h"
#include "PORTF.h"
#include "systick.h"

void gettime(unsigned char* key, int* n, int* sec);
int start(int n);
void erase(unsigned char key, int* n, int* sec);
int timer(unsigned char key, int i, int sec);
int reset();
void pause(unsigned char key);
void redlight_blink(int blinks);
void timeup(void);
void redlightn_timeup(int blinks);