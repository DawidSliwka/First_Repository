#include "led.h"
#include "timer.h"
//git test
int main(){


	LedInt();
	InitTimer0Match0(200000);
	while(1){
		LedStepLeft();
		WaitOnTimer0Match0();
	}
}

