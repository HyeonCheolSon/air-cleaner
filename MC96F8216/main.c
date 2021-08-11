//======================================================
// Main program routine
// - Device name  : MC96F8216
// - Package type : 24QFN
//======================================================
// For XDATA variable : V1.041.00 ~
#define		MAIN	1

// Generated    : Wed, Aug 11, 2021 (12:44:11)
#include	"MC96F8316.h"
#include	"func_def.h"

unsigned int i;
unsigned int p;
unsigned int count;
unsigned int period;

////////////PWM////////////////
void controlPWM(int num)
{
	if(num == 0)
	{
		T0DR = 0xFF;
	}
	else if(num == 1)
	{
		T0DR = 0x80;
	}
	else if(num == 2)
	{
		T0DR = 0x40;
	}
	else if(num == 3)
	{
		T0DR = 0x01;
	}
}
//////////////////////////////////

/////////////////////LED////////////
void onRED()
{
	offBLUE();
	offGREEN();
	P1 |= 0x02;

}
void offRED()
{
	P1 &= 0xFD;
}
void onGREEN()
{
	offBLUE();
	offRED();
	P1 |= 0x04;
}
void offGREEN()
{
	P1 &= 0xFB;
}
void onBLUE()
{
	offRED();
	offGREEN();
	P1 |= 0x08;
}
void offBLUE()
{
	P1 &= 0xF7;
}
void onYELLOW()
{
	for(i = 0; i < 2; i++)
	{
		if(i==0)
		{
			onRED();
		}
		else
		{
			onGREEN();
		}
	}
}
void onCYAN()
{
	for(i = 0; i < 2; i++)
	{
		if(i==0)
		{
			onBLUE();
		}
		else
		{
			onGREEN();
		}
	}
}

void onWHITE()
{
	for(i = 0; i < 3; i++)
	{
		if(i==0)
		{
			onRED();
		}
		else if(i==1)
		{
			onGREEN();
		}
		else
		{
			onBLUE();
		}
	}
}

///////////////////////////////////

////////RELAY//////////////////////
void onRELAY()
{
	P1 |= 0x20;
	onRED();
}
void offRELAY()
{
	P1 &= 0xDF;
	onBLUE();
}
//////////////////////////////////////

void main()
{
	cli();          	// disable INT. during peripheral setting
	port_init();    	// initialize ports
	clock_init();   	// initialize operation clock
	sei();          	// enable INT.
	
	// TODO: add your main code here
	T0CR = 0x90; // Timer 0 Control Register - PWM Mode P35
	controlPWM(2);
	while(1)
	{
		//onWHITE();
		//P1 |= 0x0E;
		//P3 = 0x20;
		//controlPWM(1);
		//controlPWM(2);
		//controlPWM(3);
		//controlPWM(1);
	}
}

//======================================================
// interrupt routines
//======================================================

//======================================================
// peripheral setting routines
//======================================================

void clock_init()
{
	// internal RC clock (1.000000MHz)
	// Nothing to do for the default clock
}

void port_init()
{
	// initialize ports
	P0IO = 0xFF;    	// direction
	P0PU = 0x00;    	// pullup
	P0OD = 0x00;    	// open drain
	P03DB = 0x00;   	// bit7~6(debounce clock), bit5~0=P35,P06~02 debounce
	P0   = 0x00;    	// port initial value

	P1IO = 0xFF;    	// direction
	P1PU = 0x00;    	// pullup
	P1OD = 0x00;    	// open drain
	P12DB = 0x00;   	// debounce : P23~20, P13~10
	P1   = 0x00;    	// port initial value

	P2IO = 0xFF;    	// direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	P2   = 0x00;    	// port initial value

	P3IO = 0xFF;    	// direction
	P3PU = 0x00;    	// pullup
	P3OD = 0x00;    	// open drain
	P3   = 0x00;    	// port initial value

	// Set port functions
	P0FSR = 0x00;   	// P0 selection
	P1FSRH = 0x00;  	// P1 selection High
	P1FSRL = 0x00;  	// P1 selection Low
	P2FSR = 0x00;   	// P2 selection
	P3FSR = 0x20;   	// P3 selection P35 pwm mode
}

