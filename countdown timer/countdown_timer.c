#include "countdown_timer.h"

void gettime(unsigned char* key, int* n, int* sec){
  (*key) = keypad_getchar();
	if((*n)==4 && (*key) !='A')
	  (*key)=0;
	
	if((*key)!=0){
		if(isdigit(*key)){
		    (*sec)*=10;
		    int temp;
			temp = (*key) - '0';
			(*sec)+=temp;
			LCD_data(*key);
			(*n)++;
		}
	}
}
int start(int n){
  if( ((GPIO_PORTF_DATA_R & Left_SW) == 0x00) && n>0){
	  LCD_command(0x0C);   //Display on, cursor off
	  LCD_data('.');
	  LCD_data('0');
	  LCD_data('0');
	  return 1;
  }
  else
	return 0;	
}

void erase(unsigned char key, int* n, int* sec){
  if(key == 'A' && n>0){
	  (*n)--;
	  LCD_command(0x80 + (*n));
	  LCD_data(' ');
	  LCD_command(0x80 + (*n));
	  (*sec)/=10;
	}
}

int timer(unsigned char key, int i, int sec){
  int l=0, m=0, o=0;
  i=0;
  int n=sec;
  int c=0;
  while(n!=0){
	n/=10;
	c++;
  }
  int temp1, temp2;
  if(c==1){
	m=0;
  	l=0;
  	i=sec-1;
  }
  
  else if(c==2){
	m=0;
	i=(sec%10)-1;
	sec/=10;
	l=sec;
  }
  else if(c==3){
	i=(sec%10)-1;
	sec/=10;
	temp1=sec%10;
	l=sec%10;
	sec/=10;
	m=sec;
  }
  else if(c==4){
	i=(sec%10)-1;
	sec/=10;
	l=sec%10;
	temp1=l;
	sec/=10;
	temp2=sec%10;
	m=sec%10;
	sec/=10;
	o=sec;
  }
  for(;o>=0;o--){
	LCD_command(0x80);
	LCD_data((o + '0'));
	
	if(o!=sec && c==4)
	  m=9; 
  for(;m>=0;m--){
	LCD_command(0x81);
	LCD_data((m + '0'));
	if(m!=sec && c==3)
	  l=9;
	else if(m!=temp2 && c==4)
	  l=9;
	
  for(;l>=0;l--){
	LCD_command(0x82);
	
	LCD_data((l + '0'));
	if(l!=sec && c==2)
	  i=9;
	else if(l!=temp1 && c==3)
	  i=9;
	else if(l!=temp1 && c==4)
	  i=9;
	
  for(;i>=0;i--){
	  LCD_command(0x83);
	  LCD_data( (i + '0' ));
	  LCD_data('.');

	  for(int j=9;j>=0;j--){
		LCD_data(j + '0');
		
		for(int k=9;k>=0;k--){
			if(reset())
			  return 1;
			pause(key);
			systick_delayMs(10);
			LCD_command(0x86);
			LCD_data(k + '0');
		}
		LCD_command(0x85);
	  }
  }
  }
  }
  }
  return 0;
}

int reset(){
  return ((GPIO_PORTF_DATA_R & Right_SW) == 0x00);
}

void pause(unsigned char key){
  key = keypad_getkey();
  if(key == '#'){
	while(1){
	  key = keypad_getkey();
	  if(key == '*')
		break;
	  }
	}
}

void redlight_blink(int blinks){
  while(blinks>0){
	  GPIO_PORTF_DATA_R = 0x2;
	  systick_delayMs(500);
	  GPIO_PORTF_DATA_R = 0x0;
	  systick_delayMs(500);
	  blinks--;
  }
}

void timeup(void){
  LCD_command(0x80);
  LCD_data('T');
  LCD_data('I');
  LCD_data('M');
  LCD_data('E');
  LCD_data(39);
  LCD_data('S');
  LCD_data(' ');
  LCD_data('U');
  LCD_data('P');
}

void redlightn_timeup(int blinks){
  while(blinks>0){
    GPIO_PORTF_DATA_R = 0x2;
	timeup();
	systick_delayMs(500);
	GPIO_PORTF_DATA_R = 0x0;
	LCD_command(1);
	systick_delayMs(500);
	blinks--;
  }
  
}