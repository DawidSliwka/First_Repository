#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET  (1<<1)

#define INTERRUPT_ON_MR0 (1<<0)
#define RESET_ON_MR0 (1<<1)
#define STOP_ON_MR0 (1<<2)

#define MR0_INTERRUPT (1<<0)

void InitTimer0(void){
	T0TCR = T0TCR | COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR = T0TCR | COUNTER_RESET;
	T0TCR = T0TCR & ~COUNTER_RESET;
	uiTime = uiTime*15;
	while(T0TC < uiTime){}
}

void InitTimer0Match0(unsigned int uiDelayTime){
	T0MR0 = uiDelayTime*15;
	T0MCR = T0MCR | (RESET_ON_MR0 | INTERRUPT_ON_MR0);
	T0TCR = T0TCR | COUNTER_RESET;
	T0TCR = T0TCR & ~COUNTER_RESET;
	T0TCR = T0TCR | COUNTER_ENABLE;
}

void WaitOnTimer0Match0(void){
	while((T0IR & MR0_INTERRUPT) != MR0_INTERRUPT){}
	//T0IR = T0IR | MR0_INTERRUPT; jesli wczesniej na bicie 2,3.. jest 1 to ponownie ja wpisuje czyli ustawiam 0
	T0IR = MR0_INTERRUPT;
}
