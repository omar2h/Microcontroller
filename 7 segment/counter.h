int increment(int counter, unsigned char digitPattern[]){
	if (counter == 15)
		counter = 0;
	else
	    counter++;
	GPIO_PORTB_DATA_R = digitPattern[counter];
	return counter;
}

int decrement(int counter, unsigned char digitPattern[]){
	if(counter == 0){
	  counter =15;
	}
	else{
		counter--;
	}
	GPIO_PORTB_DATA_R = digitPattern[counter];
	return counter;
}

int reset(int counter, unsigned char digitPattern[]){
	counter=0;
	GPIO_PORTB_DATA_R = digitPattern[counter];
	return counter;
}

void delay(int n){
  for(int i=0;i<n;i++){}
}