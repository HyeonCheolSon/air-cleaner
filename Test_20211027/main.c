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

unsigned int led_switch = 0;
int temp_pwm = 0x00;
////////////PWM////////////////
void controlPWM(int num, int pan_power)
{
	if(num == 0)
	{
		T0DR = 0x00;
	}
	else if(num == 1)
	{
		temp_pwm = 0x8C;
		T0DR = temp_pwm + 2 * pan_power;
	}
	else if(num == 2)
	{
		temp_pwm = 0xB0;
		T0DR = temp_pwm + 2 * pan_power;
	}
	else if(num == 3)
	{
		temp_pwm = 0xE3;
		T0DR = temp_pwm + 2 * pan_power;
	}
	else if(num == 4)
	{
		temp_pwm = 0xFF;
	}
	else if(num == 5)
	{
		T0DR = 0xFF;
	}
}
int tempMotor = 0x9B;
void controlMotor(int num)
{
	T0DR = tempMotor + num;
}
//////////////////////////////////

/////////////////////LED////////////
void onRED()
{
	offGREEN();
	offBLUE();
	P1 |= 0x02;
}
void offRED()
{
	P1 &= 0xFD;
}
void onGREEN()
{
	offRED();
	offBLUE();
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
	if(led_switch == 0)
	{
		onRED();
	}
	else
	{
		onGREEN();
	}
}
void onMAGENTA()
{
	if(led_switch == 0)
	{
		onRED();
	}
	else
	{
		onBLUE();
	}
}

void onCYAN()
{
	if(led_switch == 0)
	{
		onGREEN();
	}
	else
	{
		onBLUE();
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
}
void offRELAY()
{
	P1 &= 0xDF;
}
//////////////////////////////////////

void delay_10us()
{
	_nop_(); _nop_(); _nop_(); _nop_(); _nop_();
	_nop_(); _nop_(); _nop_(); _nop_(); 
}

void delay_sec(int num)
{
	int i22;
	int j22;
	
	for(j22 = 0; j22 < num ; j22++)
		for(i22 = 0 ; i22<25000 ; i22++)
			delay_10us();
	
}
unsigned int led_color = 9;

// T0 Interrupt///////////////
void TIMER0_Int() interrupt 13
{
	if(led_switch == 0)
	{
		led_switch = 1;
	}
	else
	{
		led_switch = 0;
	}
	if(led_color == 0)
	{
		onRED();
	}
	else if(led_color == 1)
	{
		onYELLOW();
	}
	else if(led_color == 2)
	{
		onGREEN();
	}
	else if(led_color == 3)
	{
		onCYAN();
	}
	else if(led_color == 4)
	{
		onBLUE();
	}
	else if(led_color == 5)
	{
		onMAGENTA();
	}
	else if(led_color == 99)
	{
		offRED();
		offBLUE();
		offGREEN();
	}
}

/////////////////////////
int tmp = 0x00;
int tmp_count = 0;
int auto_flag = 0;

void UARTRX_Int() interrupt 9
{
	// tmp_old = tmp;
	tmp = UARTDR;
	
	//if(tmp == tmp_old)
	//{
	//	tmp_count += 1;
	//	if(tmp_count == 2)
	//	{
	//		ctrl_variable = tmp;
	//		tmp_count = 0;
	//	}
	//}
	//else if(tmp != tmp_old)
	//{
	//	tmp_count = 0;
	//}
	if(tmp == 0xC0)
	{
		auto_flag = 0;
	}
	else if(tmp == 0xD0)
	{
		auto_flag = 1;
	}
	
	P3FSR |= 0x01;
	UARTDR = tmp;
}
///////////////////////////
int pwm_ctrl;
int pan_power;
void main()
{
	cli();          	// disable INT. during peripheral setting
	port_init();    	// initialize ports
	//clock_init();   	// initialize operation clock
	UART_init();
	sei();          	// enable INT.
	
	// TODO: add your main code here
	T0CR = 0x92; // Timer 0 Control Register - PWM Mode P35
	
	//T1CRH = 0x80;
	//T1CRL = 0x20; // Timer 1 Low Control Register
	
	//offRED();
	//offGREEN();
	//offBLUE();
	//onRELAY();
	//controlPWM(0);
	IE2 = 0x02;
	IE1 = 0x08; // Rx Interrupt
	
	tmp = 0xFF;
	T0CR = 0x92;

	//T1CRL = 0x00;
	//T1CRH = 0x00;
	//T2CRL = 0x00;
	//T2CRH = 0x00;
	
	//P1FSRL = 0x00;
	//P1FSRH = 0x00;
	
	// P3FSR = 0x00;
	
	//T1ADRH = 0x00;
	////T1ADRL = 0x00;
	//T1BDRH = 0x00;
	//T1BDRL = 0x00;
	
	//T2ADRH = 0x00;
	//T2ADRL = 0x00;
	//T2BDRH = 0x00;
	//T2BDRL = 0x00;
	
	// offRELAY();
	
	// P3 = 0x20;
//	led_color = 3;
//	controlPWM(1);// red
//	led_color = 0;
//	delay_sec(20);
//	controlPWM(2);
//	led_color = 1;// yellow
//	delay_sec(20);
//	controlPWM(3);
//	led_color =2; // green
//	delay_sec(20);
//	controlPWM(4);
//	led_color = 3; // cyan
//	delay_sec(20);
	
//	controlPWM(3);
//	led_color = 2; // green
//	delay_sec(20);
//	controlPWM(2);
//	led_color = 1; // yellow
//	delay_sec(20);
		UARTDR = 0xFF;
		T0DR = 0x00;
		led_color = 4;
		pwm_ctrl = 0;
		pan_power = 0;
	while(1)
	{
		
		// onRELAY();
		// controlPWM(3);
		// led_color = 0;

		
		
		// red 0
		// yellow 1
		// green 2
		// cyan 3 
		// blue 4
		// magenta 5
		//controlPWM(4);
		//tmp = UARTDR;
		// A0 : off
		
		//UARTDR = tmp;
		if(auto_flag == 0)
		{
			switch (tmp)
			{
			case 0xF1: // air condition GOOD scenario
				pwm_ctrl = 1;
				controlPWM(1, pan_power);
				led_color = 3; //cyan
				onRELAY();
				tmp = 0x00;
				break;
			case 0xF2: // air condition SOSO scenario
				pwm_ctrl = 2;
				controlPWM(2, pan_power);
				led_color = 2; // green
				onRELAY();
				tmp = 0x00;
				break;
			case 0xF3: // air condition BAD scenario
				pwm_ctrl = 3;
				controlPWM(3, pan_power);
				led_color = 1; // yellow
				onRELAY();
				tmp = 0x00;
				break;
			case 0xF4: // air condition VERY BAD scenario
				pwm_ctrl = 4;
				controlPWM(4, pan_power);
				led_color = 0; // red
				onRELAY();
				tmp = 0x00;
				break;
			case 0xB1:
				pan_power = 0;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB2:
				pan_power = 1;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB3:
				pan_power = 2;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB4:
				pan_power = 3;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB5:
				pan_power = 4;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB6:
				pan_power = 5;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB7:
				pan_power = 6;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB8:
				pan_power = 7;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xB9:
				pan_power = 8;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			case 0xBA:
				pan_power = 9;
				controlPWM(pwm_ctrl, pan_power);
				tmp = 0x00;
				break;
			
			case 0xA0:
				pwm_ctrl = 0;
				controlPWM(0, pan_power);
				led_color = 99; // red
				offRELAY();
				tmp = 0x00;
				break;
			}
		}
		else
		{
			if(tmp > 0x00 && tmp < 0x65)
			{
				controlMotor(tmp);
			}
			else if(tmp == 0xA0)
			{
				controlPWM(0, pan_power);
				led_color = 99; // red
				offRELAY();
			}
		}
		
		/*
		case 0x01: 
			led_color = 0; // red
			break;
		case 0x02: 
			led_color = 2; // green
			break;
		case 0x03: 
			led_color = 4; // blue
			break;
		case 0x04: 
			led_color = 3; // cyan
			break;
		case 0x05: 
			led_color = 1; // yellow
			break;
		case 0x06: 
			led_color = 5; // magenta
			break;
		*/
		

		//case 0x01: 
		//	controlPWM(0); // 60% duration
		//	break;
		//case 0x02: 
		//	controlPWM(2); // 70% duration
		//	break;
		//case 0x03: 
		//	controlPWM(3); // 80% duration
		//	break;
		//case 0x04: 
		//	controlPWM(4); // 90% duration
		//	break;
		//case 0x05: 
		//	controlPWM(5); // 100% duration
		//	break;
		
		//case 0x21: 
		//	onRELAY(); // relay on
		//	break;
		//case 0x22: 
		//	offRELAY(); // relay off
		//	break;
		/*
		
		*/
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

void UART_init()
{
	// initialize UART interface
	// ASync. 9615bps N 8 1
	UARTCR2 = 0x02; 	// activate UART
	UARTCR1 = 0x06; 	// bit count, parity
	UARTCR2 |= 0x2F;	// interrupt, speed
	UARTCR3 = 0x00; 	// stop bit
	UARTBD = 0x1D;  	// baud rate 1D
	UARTST=0x60;	  //UDRE TXC RXC WAKE SOFTRST DOR FE PE 
  // 0x40
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

	P3IO = 0xFD;    	// direction
	P3PU = 0x00;    	// pullup
	P3OD = 0x00;    	// open drain
	P3   = 0x00;    	// port initial value

	// Set port functions
	P0FSR = 0x00;   	// P0 selection
	P1FSRH = 0x00;  	// P1 selection High
	P1FSRL = 0x00;  	// P1 selection Low
	P2FSR = 0x00;   	// P2 selection
	// P3FSR = 0x00;   	// P3 selection P35 GPIO mode
	P3FSR = 0x20;   	// P3 selection P35 pwm mode
}

