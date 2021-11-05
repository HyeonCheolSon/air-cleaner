//======================================================
// Main program routine
// - Device name  : MC96FR332A
// - Package type : 28TSSOP
//======================================================
// For XDATA variable : V1.041.00 ~
#define		MAIN	1

// Generated    : Thu, Mar 17, 2016 (21:23:38)
#include <stdio.h>
#include <string.h>
#include	"MC96FR332A.h"
#include	"func_def.h"

#define PWM0_FLAG 	0x01
#define PWM1_FLAG 	0x02
#define PWM2_FLAG 	0x04
#define PWM3_FLAG 	0x08

#define PWM_CTL_OFF		0
#define PWM_CTL_INC		1
#define PWM_CTL_DEC		2

#define GFLAG_WAKEUP	0x01

// ----------------------------------
#define PWM_CH_NUM		4

 

unsigned int _uart_tx_count, _uart_rx_count;
unsigned int _uart_tx_len,   _uart_rx_len;

bit _uart_tx_complete = 0;
bit _uart_rx_complete = 0;

unsigned char _uart_tx_err = 0;
unsigned char _uart_rx_err = 0;
unsigned char UART_BUFFER_SIZE = 8;
unsigned char _uart_rx_buf[8] = {0};
unsigned char _uart_tx_buf[8] = {0};

unsigned int _IdleCounter = 0;



void UART1_Clear()
{
	int i;

	_uart_tx_count = 0;
	_uart_rx_count = 0;

	for(i=0; i < UART_BUFFER_SIZE; i++) {
		_uart_rx_buf[i] = 0;
		_uart_tx_buf[i] = 0;
	}
	UDATA1 = 0xFF;
	
}


void UART1_Init()
{
	char cc01, cc02, cc03;

	//UDRIE TXCIE RXCIE WAKEIE TXE RXE USARTEN U2X
	cc02 = ( 0 << 7 ) // 0   : Transmit data empty interrupt disable 
						//_1   : Transmit data empty interrupt enable
			|( 0 << 6 ) // 0   : Transmit completed interrupt disable 
						//_1   : Transmit completed interrupt enable
			|( 0 << 5 ) // 0   : Recv completed Interrupt disable 
						//_1   : Recv completed Interrupt enable
			|( 0 << 4 ) // 0   : Wake up interrupt disable
						//_1   : Wake up interrupt enable
			|( 0 << 3 ) // 0   : TX disable
						//_1   : TX enable
			|( 1 << 2 ) // 0   : Rx disable
						//_1   : Rx enable
			|( 1 << 1 ) // 0   : USART disable
						//_1   : USART enable
			|( 1 << 0 );// 0   : Double speed disable in Asyncronous mode
						//_1   : Double speed enable in Asyncronous mode

	//Synchronous mode 
	//UMSEL1 UMSEL0 UPM1 UPM0 USIZE2 USIZE1(UDORD) USIZE0(UCPHA) UCPOL
	cc01 = ( 0 << 7 ) // 00  : Asyncronous mode( Uart ) 
			|( 0 << 6 ) // 01  : Syncronouse mode
						//_11  : SPI mode
			|( 0 << 5 ) // 00  : No parity
			|( 0 << 4 ) // 10  : Even parity
						//_11  : Odd parity
			|( 0 << 3 ) // 000 : 5 bit data frame 
			|( 1 << 2 ) // 001 : 6 bit data frame   
			|( 1 << 1 ) // 010 : 7 bit data frame    
						// 011 : 8 bit data frame
						//_111 : 9 bit data frame
			|( 0 << 0 );// 0   : In syncronouse mode -> TXD change at rising, RXD change at falling
						// 1   : In syncronouse mode -> RXD change at rising, TXD change at falling


	//MASTER LOOPS DISXCK SPISS - USBS TX8 RX8
	cc03 = ( 0 << 7 ) 	// 0   : Slave mode ( XCL in ) in SPI and Syncronous mode
						//_1   : Master mode ( XCL out ) in SPI and Syncronous mode
			|( 0 << 6 ) // 0   : Normal mode
						//_1   : Loop back mode
			|( 0 << 5 ) // 0   : XCK out always ( when only USART is enabled ) ,in Sync mode
						//_1   : XCK out when only TX is tranmitting           ,in Sync mode
			|( 0 << 4 ) // 0   : SS out disable in SPI Master mode
						//_1   : SS out enable in SPI Master mode
			|( 0 << 3 ) //     : nothing
			|( 0 << 2 ) // 0   : 1 stop bit in UART mode	//V1.4
						//_1   : 2 stop bit in UART mode
			|( 0 << 1 ) // x   : 9th TX data bit in UART mode
			|( 0 << 0 );// x   : 9th RX data bit in UART mode 


	UCTRL12=0x00;
	UCTRL11=0x00;
	UCTRL13=0x00;

	UCTRL12=0x02;	//UDRIE TXCIE RXCIE WAKEIE TXE RXE USARTEN U2X
	UCTRL12=cc02;	//UDRIE TXCIE RXCIE WAKEIE TXE RXE USARTEN U2X
	UCTRL11=cc01;	//UMSEL1 UMSEL0 UPM1 UPM0 USIZE2 USIZE1(UDORD) USIZE0(UCPHA) UCPOL
	UCTRL13=cc03;  //MASTER LOOPS DISXCK SPISS - USBS TX8 RX8

	//UBAUD1 = 3;  //115200 bps : 4.000000 MHz, ubaud=3  (ERROR:8.5%, U2X=1)
	//UBAUD1 = 7;  //115200 bps : 7.372800 MHz, ubaud=7  (ERROR:0%, U2X=1)
	//UBAUD1 = 95; //9600	  bps : 7.372800 MHz, ubaud=95 (ERROR:0%, U2X=1)
	UBAUD1 = 95;

	USTAT1=0x60;	  //UDRE TXC RXC WAKE SOFTRST DOR FE PE 

	// Interrupt Priority Register (IP, IP1)
	//IP	|= 0x04;	//RX0(GROUP2)
	//IP1	|= 0x04;	//RX0(GROUP2)


	//IE1	|= 0x20;  //- - INT11E(RX1) INT10E(TX0) INT9E(RX0) INT8E(BOD) INT7E(IRI) INT6E(Reserved)
	//IE2	|= 0x01;  //- - INT17E(I2C) INT16E(T3) INT15E(T2) INT14E(T1) INT13E(T0) INT12E(TX1)

	_uart_rx_count = 0;
	_uart_tx_count = 0;


	//cc01 = UDATA1;
}




void RX1_Int()
{
	unsigned char RX0Data;

	RX0Data = UDATA1;

	//strcpy(_uart_rx_buf, UDATA1);
	
	if(USTAT1 & 0x03) 	//UDRE TXC RXC WAKE SOFTRST DOR FE PE
	{
	}

	else if(_uart_rx_count == 0)
	{
		_uart_rx_len = 8;
		_uart_rx_buf[0] = RX0Data;
		_uart_rx_count = 1;
	}
	
	while (_uart_rx_count < 7)
	{
		
		_uart_rx_buf[_uart_rx_count] = RX0Data;
		_uart_rx_count++;

		//RESET_IDLE;
	}
}



typedef struct _tagPWMINFO {
	int 	period;
	int 	duty;
	int 	default_duty;
	int 	next_duty;
	int 	count;
	int		out;
} PWMINFO;



static unsigned int _pwm_ctl_dec_flag = 0;
static unsigned int _pwm_ctl_inc_flag = 0;
static unsigned int _pwm_ctl_cnt = 0;

static unsigned int _pwm_flag_list[PWM_CH_NUM] = { PWM0_FLAG, PWM1_FLAG, PWM2_FLAG, PWM3_FLAG };



// ----------------------------------
static int _pwm_mask = 0x0f;	// Enable Mask : - - - - PWM3 PWM2 PWM1 PWM0
PWMINFO 	_pwm[PWM_CH_NUM];


static char _pwm_out;



//======================================================
// peripheral setting routines
//======================================================

void clock_init()
{
	// Nothing to do for the default clock
	//SCCR |= 0x10; 	// set CBYS
}


// initialize ports
void port_init()
{
	// P0
	P0IO = 0xFF;    	// direction
	P0PU = 0xFF;    	// pullup
	P0BPC = 0xFF;   	// BPC
	P0   = 0x00;    	// port initial value

	// P1
	P1IO = 0x00;    	// direction
	P1PU = 0x00;    	// pullup
	P1OD = 0x00;    	// open drain
	P1BPC = 0x00;   	// BPC
	P1   = 0x00;    	// port initial value

	// P2
	P2IO = 0xFF;    	// direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	P2BPC = 0x00;   	// BPC
	P2   = 0x00;    	// port initial value

	// P3
	P3IO = 0xFF;    	// direction
	P3PU = 0xFF;    	// pullup
	P3OD = 0x00;    	// open drain
	P3BPC = 0x00;   	// BPC
	P3   = 0x00;    	// port initial value

	PSR0 = 0x00;    	// port selection
						// SDASWAP SCLSWAP SS0SWAP XCK0SWAP INT3SWAP INT2SWAP INT1SWAP INT0SWAP
						// INT3SWAP = 1 : External interrupt 3 is triggered on P15 instead of P22
						// INT2SWAP = 1 : External interrupt 2 is triggered on P14 instead of P21
						// INT1SWAP = 1 : External interrupt 1 is triggered on P13 instead of P37
						// INT0SWAP = 1 : External interrupt 0 is triggered on P12 instead of P36
}




//======================================================
// PWM
//======================================================

// period, duty unit : T1 interrupt interval
void pwm_setup( PWMINFO *pwm, int period, int duty )
{
	pwm->period 		= period;
	pwm->duty   		= duty;
	pwm->next_duty  	= duty;
	pwm->default_duty	= duty;
	pwm->count  	= 0;
	pwm->out 		= 0;
}


void pwm_init()
{

	pwm_setup( &_pwm[0], 10, 0 );
	pwm_setup( &_pwm[1], 10, 7 );
	pwm_setup( &_pwm[2], 10, 8 );
	pwm_setup( &_pwm[3], 10, 9 );

}

//======================================================
// Timer
//======================================================
void timer_init()
{
	//cli();

	// Enable T0 Timer
	IE2 	|= 0x02;

	T0CR 	= 0x97;	// T0EN T0_PE CAP0 T0CK2 T0CK1 T0CK0 T0CN T0ST
					//   1    0     0    1    0       1    1    1   (0x97)
					//		T0EN : Enable or disable Timer0
					//		T0_PE : T0 pin out enable
					//		CAP0 : Timer0 capture mode (0=Timer mode, 1=Capture mode)
					//		T0CK[2:0] : clock source
					//			(base Fsclk : 7.3728 MHz)
					//			000 : Fsclk / 2 	: 3.6864 MHz : 0.2712 us
					//			001 : Fsclk / 4		: 1.8432 MHz : 0.5415 us
					//			010 : Fsclk / 16	: 0.4608 MHz : 2.17   us
					//			...
					//			101 : Fsclk / 1024  : 7,200  Hz  : 0.1388 ms (1000/0.13888 = 720)
					//			110 : Fsclk / 4096  : 1,800  Hz  : 0.5555 ms
					//		T0CN : pause or continue counting (0=Pause 1=Continue)
					//		T0ST : start or stop (0=Stop 1=Clear and start)

	T0DR	= 72;	

	//sei();
}


//======================================================
void pwm_setup_control( unsigned int pwmflag, unsigned int ctl )
{
	if( ctl == PWM_CTL_OFF ) 
	{
		_pwm_ctl_inc_flag &= ~pwmflag;
		_pwm_ctl_dec_flag &= ~pwmflag;
	}
	else if( ctl == PWM_CTL_DEC ) 
	{
		_pwm_ctl_dec_flag |=  pwmflag;
		_pwm_ctl_inc_flag &= ~pwmflag;
	}
	else 
	{
		_pwm_ctl_dec_flag &= ~pwmflag;
		_pwm_ctl_inc_flag |=  pwmflag;
	}
}


//======================================================
void pwm_control()
{

	// 60, 70, 80, 90, 100

	_pwm_out = 0;

	// PWM 0
	if( _pwm[0].count < _pwm[0].duty && (_pwm_mask & PWM0_FLAG) ) {
		_pwm_out |= 0x01;	// P00
	}

	_pwm[0].count++;

	
	if( _pwm[0].count >= _pwm[0].period ) {
		_pwm[0].count = 0;
		_pwm[0].duty  = _pwm[0].next_duty;
	}


	// PWM 1
	if( _pwm[1].count < _pwm[1].duty && (_pwm_mask & PWM1_FLAG) ) {
		_pwm_out |= 0x02;	// P01
	}

	_pwm[1].count++;

	if( _pwm[1].count >= _pwm[1].period ) {
		_pwm[1].count = 0;
		_pwm[1].duty  = _pwm[1].next_duty;
	}


	// PWM 2
	if( _pwm[2].count < _pwm[2].duty && (_pwm_mask & PWM2_FLAG) ) {
		_pwm_out |= 0x04;	// P02
	}

	_pwm[2].count++;

	if( _pwm[2].count >= _pwm[2].period ) {
		_pwm[2].count = 0;
		_pwm[2].duty  = _pwm[2].next_duty;
	}


	// PWM 3
	if( _pwm[3].count < _pwm[3].duty && (_pwm_mask & PWM3_FLAG) ) {
		_pwm_out |= 0x08;	// P03
	}

	_pwm[3].count++;

	
	if( _pwm[3].count >= _pwm[3].period ) {
		_pwm[3].count = 0;
		_pwm[3].duty  = _pwm[3].next_duty;
	}


	P0 = _pwm_out;


}

void pwm_enable( int pwm0, int pwm1, int pwm2, int pwm3 )
{
	// 0:Disable 1:Enable -1:Don't care(not change)

	// B/G/R/Motor
	if( pwm0 != -1 ) { if( pwm0 ) _pwm_mask |= PWM0_FLAG; else _pwm_mask &= ~PWM0_FLAG; }
	if( pwm1 != -1 ) { if( pwm1 ) _pwm_mask |= PWM1_FLAG; else _pwm_mask &= ~PWM1_FLAG; }
	if( pwm2 != -1 ) { if( pwm2 ) _pwm_mask |= PWM2_FLAG; else _pwm_mask &= ~PWM2_FLAG; }
	if( pwm3 != -1 ) { if( pwm3 ) _pwm_mask |= PWM3_FLAG; else _pwm_mask &= ~PWM3_FLAG; }
}

//======================================================
void setupOpMode()
{
	pwm_setup_control( PWM0_FLAG, PWM_CTL_OFF );
	pwm_setup_control( PWM1_FLAG, PWM_CTL_OFF );
	pwm_setup_control( PWM2_FLAG, PWM_CTL_OFF );
	pwm_setup_control( PWM3_FLAG, PWM_CTL_OFF );

}





void setPWM()
{	

	if(UDATA1 == 0x00)
	{
		pwm_enable(0, -1, -1, -1);
		UART1_Clear();
	}
			
	else if(UDATA1 == 0x01)
	{
		pwm_enable( 1, -1,-1,-1 );
		pwm_setup( &_pwm[0], 10, 6 );
		UART1_Clear();
	}
		
	else if(UDATA1 == 0x02)
	{
		pwm_enable( 1, -1,-1,-1 );
		pwm_setup( &_pwm[0], 10, 7 );
		UART1_Clear();
	}	

	else if(UDATA1 == 0x03)
	{
		pwm_enable( 1, -1,-1,-1 );
		pwm_setup( &_pwm[0], 10, 8 );
		UART1_Clear();
	}	
	
	else if(UDATA1 == 0x04)
	{
		pwm_enable( 1, -1,-1,-1 );
		pwm_setup( &_pwm[0], 10, 9 );
		UART1_Clear();
	}	

	
	else if(UDATA1 == 0x05)
	{
		pwm_enable( 1, -1,-1,-1 );
		pwm_setup( &_pwm[0], 10, 10 );
		UART1_Clear();
	}

	
	
	/*
	if (_i2c_rx_buf == 0x00 )
		pwm_enable(0, 0, 0, -1);
	
	else if (_i2c_rx_buf == 0x01 )
		pwm_setup( &_pwm[0], 10, 6 );
	
	else if (_i2c_rx_buf == 0x02 )
		pwm_setup( &_pwm[0], 10, 7 );
	
	else if (_i2c_rx_buf == 0x04 )
		pwm_setup( &_pwm[0], 10, 8 );
	
	else if (_i2c_rx_buf == 0x08 )
		pwm_setup( &_pwm[0], 10, 9 );
	
	else if (_i2c_rx_buf == 0x10 )
		pwm_setup( &_pwm[0], 10, 10 );
	*/
	
	
}





//======================================================
// main
//======================================================
void main()
{
	int i;
	int datalength = 0;
	
	cli();          	// disable INT. during peripheral setting
	port_init();    	// initialize ports
	clock_init();   	// initialize operation clock
	pwm_enable( 1, 1, 1, 1 );	
	pwm_init();
	timer_init();
	UART1_Init();

	sei();          	// enable INT.

	UDATA1 = 0xFF;
	
	for(i = 0; i < 1000; i++) _nop_();	// init delay
	setupOpMode();

	while(1)
	{		
		for (i= 0; i < 10; i++)
			pwm_control();
		
		if (UDATA1 < 0x06)
		{
			setPWM();
			//pwm_control();
		}
		
	}
}
