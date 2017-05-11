#include "LPC11xx.h"                    // Device header

uint8_t table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

int counter = 0;



void PIOINT3_IRQHandler()

{

	if ((LPC_GPIO3->MIS&(1<<2))==(1<<2))

	{

		counter++;

		LPC_GPIO3->IC=(1<<2);

	}

}

void delay()

{

	uint16_t i=4000;

	while(i--);

}

void BreakInit()

{

	LPC_GPIO3->IE|=(1<<2);

	LPC_GPIO3->IS&=~(1<<2);

	LPC_GPIO3->IEV&=~(1<<2);

}

void SEGinit()

{

	LPC_GPIO2->DIR|=0xFFF;

}

void KEYinit()

{

	LPC_GPIO3->DIR &=~(1<<2);

}

void display(int value)

{

		LPC_GPIO2->DATA &=~(0xff);

		LPC_GPIO2->DATA |= table[value%1000%1000%10];

		LPC_GPIO2->DATA &=~(1<<11);

		delay();

		LPC_GPIO2->DATA = 0xFFF;

		

		LPC_GPIO2->DATA &=~(0xff);

		LPC_GPIO2->DATA |= table[value%1000%100/10];

		LPC_GPIO2->DATA &=~(1<<10);

		delay();

		LPC_GPIO2->DATA = 0xFFF;

	

		LPC_GPIO2->DATA &=~(0xff);

		LPC_GPIO2->DATA |= table[value%1000/100];

		LPC_GPIO2->DATA &=~(1<<9);

		delay();

		LPC_GPIO2->DATA = 0xFFF;

	

		LPC_GPIO2->DATA &=~(0xff);

		LPC_GPIO2->DATA |= table[value/1000];

		LPC_GPIO2->DATA &=~(1<<8);

		delay();

		LPC_GPIO2->DATA = 0xFFF;

}



int main()

{

	SEGinit();

	KEYinit();

	BreakInit();

	NVIC_EnableIRQ(EINT3_IRQn);

	while(1)

	{

		display(counter);

	}

}








