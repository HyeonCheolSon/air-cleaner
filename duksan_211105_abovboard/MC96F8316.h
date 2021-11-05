#include		"compiler.h"

#if defined __ICC8051__		// IAR
#include		<intrinsics.h>
#define		NOP			__no_operation()
#else						// KEIL
#include		<intrins.h>
#define		NOP			_nop_()
#endif

//======================================================
//		device   : MC96F8316(32 pin)
//		version  : Ver1.0  
//		date     : 2011-10-14
//		compiler : Keil-C
//		author   : Ma, Nakwon
//======================================================


#ifndef		_MC96F8316_
#define		_MC96F8316_

SFR(P0, 0x80);	// P0 Data Register
	SBIT(P00, 0x80, 0);
	SBIT(P01, 0x80, 1);
	SBIT(P02, 0x80, 2);
	SBIT(P03, 0x80, 3);
	SBIT(P04, 0x80, 4);
	SBIT(P05, 0x80, 5);
	SBIT(P06, 0x80, 6);
	SBIT(P07, 0x80, 7);

SFR(P0IO, 0xA1);	// P0 Direction Register
SFR(P0OD, 0x91);	// P0 Open-drain Selection Register
SFR(P0PU, 0xAC);	// P0 Pull-up Resistor Selection Register
SFR(P03DB, 0xDE);	// P0/P3 Debounce Enable Register

SFR(P1, 0x88);	// P1 Data Register
	SBIT(P10, 0x88, 0);
	SBIT(P11, 0x88, 1);
	SBIT(P12, 0x88, 2);
	SBIT(P13, 0x88, 3);
	SBIT(P14, 0x88, 4);
	SBIT(P15, 0x88, 5);
	SBIT(P16, 0x88, 6);
	SBIT(P17, 0x88, 7);
	
SFR(P1IO, 0xB1);	// P1 Direction Register
SFR(P1OD, 0x92);	// P1 Open-drain Selection Register
SFR(P1PU, 0xAD);	// P1 Pull-up Resistor Selection Register
SFR(P12DB, 0xDF);	// P1/P2 Debounce Enable Register

SFR(P2, 0x90);	// P2 Data Register
	SBIT(P20, 0x90, 0);
	SBIT(P21, 0x90, 1);
	SBIT(P22, 0x90, 2);
	SBIT(P23, 0x90, 3);
	SBIT(P24, 0x90, 4);
	SBIT(P25, 0x90, 5);
	SBIT(P26, 0x90, 6);
	SBIT(P27, 0x90, 7);

SFR(P2IO, 0xB9);	// P2 Direction Register
SFR(P2OD, 0x93);	// P2 Open-drain Selection Register
SFR(P2PU, 0xAE);	// P2 Pull-up Resistor Selection Register

SFR(P3, 0x98);	// P3 Data Register
	SBIT(P30, 0x98, 0);
	SBIT(P31, 0x98, 1);
	SBIT(P32, 0x98, 2);
	SBIT(P33, 0x98, 3);
	SBIT(P34, 0x98, 4);
	SBIT(P35, 0x98, 5);
	SBIT(P36, 0x98, 6);
	SBIT(P37, 0x98, 7);

SFR(P3IO, 0xC1);	// P3 Direction Register
SFR(P3OD, 0x94);	// P3 Open-drain Selection Register
SFR(P3PU, 0xAF);	// P3 Pull-up Resistor Selection Register
   			
SFR(P0FSR, 0xD3);	//P0 Function Selection Register
SFR(P1FSRL, 0xD4);	//P1 Function Selection Low Register
SFR(P1FSRH, 0xD5);	//P1 Function Selection High Register
SFR(P2FSR, 0xD6);	//P2 Function Selection Register
SFR(P3FSR, 0xD7);	//P3 Function Selection Register

// Interrupt Control
SFR(IE, 0xA8);	// Interrupt Enable Register 0
SFR(IE1, 0xA9);	// Interrupt Enable Register 1
SFR(IE2, 0xAA);	// Interrupt Enable Register 2
SFR(IE3, 0xAB);	// Interrupt Enable Register 3
SFR(IP, 0xB8);	// Interrupt Priority Register 0
SFR(IP1, 0xF8);	// Interrupt Priority Register 1
SFR(IIFLAG, 0xA0);	// Internal Interrupt Flag Register
SFR(EIFLAG0, 0xC0);	// External Interrupt Flag 0 Register
SFR(EIFLAG1, 0xB0);	// External Interrupt Flag 1 Register
SFR(EIPOL0L, 0xA4);	// External Interrupt Polarity 0 Low Register
SFR(EIPOL0H, 0xA5);	// External Interrupt Polarity 0 High Register
SFR(EIPOL1, 0xA6);	// External Interrupt Polarity 1 Register
SFR(EIPOL2, 0xA7);	// External Interrupt Polarity 2 Register

// System Oscillator, Reset Control
SFR(SCCR, 0x8A);	// System Clock Control Register
SFR(OSCCR, 0xC8);	// Oscillator Control Register
SFR(BITCNT, 0x8C);	// Basic Interval Timer Counter Register
SFR(BITCR, 0x8B);	// Basic Interval Timer Control Register
SFR(RSTFR, 0xE8);	// Reset Flag Register
SFR(PCON, 0x87);	// Power Control Register
SFR(LVRCR, 0xD8);	// Low Voltage Reset Control Register
SFR(LVICR, 0x86);	// Low Voltage Indicator Control Register

//  Watch Dog Timer Control 
SFR(WDTDR, 0x8E);	// Watch Dog Timer Data Register
SFR(WDTCNT, 0x8E);	// Watch Dog Timer Counter Register
SFR(WDTCR, 0x8D);	// Watch Dog Timer Control Register

//  Watch Timer Control
SFR(WTDR, 0x89);	// Watch Timer Data Register
SFR(WTCNT, 0x89);	// Watch Timer Counter Register
SFR(WTCR, 0x96);	// Watch Timer Control Register

// TIMER 0 Control
SFR(T0CR, 0xB2);	// Timer 0 Control Register
SFR(T0CNT, 0xB3);	// Timer 0 Counter Register
SFR(T0DR, 0xB4);	// Timer 0 Data Register
SFR(T0CDR, 0xB4);	// Timer 0 Capture Data Register

// TIMER interrupt Control
//sfr   TIFR    =  0xC3;// Timer Interrupt Flag Register

// TIMER 1 Control
SFR(T1CRL, 0xBA);	// Timer 1 Control Low Register
SFR(T1CRH, 0xBB);	// Timer 1 Control High Register
SFR(T1ADRL, 0xBC);	// Timer 1 A Data Low Register
SFR(T1ADRH, 0xBD);	// Timer 1 A Data High Register
SFR(T1BDRL, 0xBE);	// Timer 1 B Data Low Register
SFR(T1BDRH, 0xBF);	// Timer 1 B Data High Register

// TIMER 2 Control
SFR(T2CRL, 0xC2);	// Timer 2 Control Low Register
SFR(T2CRH, 0xC3);	// Timer 2 Control High Register
SFR(T2ADRL, 0xC4);	// Timer 2 A Data Low Register
SFR(T2ADRH, 0xC5);	// Timer 2 A Data High Register
SFR(T2BDRL, 0xC6);	// Timer 2 B Data Low Register
SFR(T2BDRH, 0xC7);	// Timer 2 B Data High Register

// BUZZER Control
SFR(BUZDR, 0x8F);	// BUZZER Data Register
SFR(BUZCR, 0x97);	// BUZZER Control Register

// ADC Contol
SFR(ADCCRL, 0x9C);	// A/D Converter Control Low Register
SFR(ADCCRH, 0x9D);	// A/D Converter Control High Register
SFR(ADCDRL, 0x9E);	// A/D Converter Data Low Register
SFR(ADCDRH, 0x9F);	// A/D Converter Data High Register

SFR(ADWRCR0, 0xF2);	// ADC Wake-up Resistor Control Register 0
SFR(ADWRCR1, 0xF3);	// ADC Wake-up Resistor Control Register 1
SFR(ADWRCR2, 0xF4);	// ADC Wake-up Resistor Control Register 2
SFR(ADWRCR3, 0xF5);	// ADC Wake-up Resistor Control Register 3
SFR(ADWCRL, 0xF6);	// ADC Wake-up Control Low Register
SFR(ADWCRH, 0xF7);	// ADC Wake-up Control High Register
SFR(ADWIFRL, 0xDC);	// ADC Wake-up Interrupt Flag Low Register
SFR(ADWIFRH, 0xDD);	// ADC Wake-up Interrupt Flag High Register

// SPI(SIO) Control
SFR(SPICR, 0xB5);	// SPI Control Register
SFR(SPIDR, 0xB6);	// SPI Data Register
SFR(SPISR, 0xB7);	// SPI Status Register

// UART Control
SFR(UARTCR1, 0xE2);	// UART Control Register 1
SFR(UARTCR2, 0xE3);	// UART Control Register 2
SFR(UARTCR3, 0xE4);	// UART Control Register 3
SFR(UARTST, 0xE5);	// UART Status Register
SFR(UARTBD, 0xE6);	// UART BaudRate Register
SFR(UARTDR, 0xE7);	// UART Data Register

// I2C Control
SFR(I2CCR, 0xE9);	// I2C Control Register
SFR(I2CSR, 0xEA);	// I2C Status Register
SFR(I2CSAR0, 0xEB);	// I2C Slave Address 0 Register
SFR(I2CSAR1, 0xF1);	// I2C Slave Address 1 Register
SFR(I2CDR, 0xEC);	// I2C Data Register
SFR(I2CSDHR, 0xED);	// I2C SDA Hold Time Register
SFR(I2CSCLR, 0xEE);	// I2C SCL Low Period Register
SFR(I2CSCHR, 0xEF);	// I2C SCL High Period Register

// Flash Memory Control
SFR(FSADRH, 0xFA);	// Flash Sector Address High Register
SFR(FSADRM, 0xFB);	// Flash Sector Address Middle Register
SFR(FSADRL, 0xFC);	// Flash Sector Address Low Register
SFR(FIDR, 0xFD);	// Flash Identification Register
SFR(FMCR, 0xFE);	// Flash Mode Control Register

SFR(ACC, 0xE0);
SFR(B, 0xF0);
SFR(PSW, 0xD0);
SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);
SFR(DPL1, 0x84);
SFR(DPH1, 0x85);
SFR(EO, 0xA2);	// EXTENDED OPERATION REGISTER

#endif	//_MC96F8316_

#define		cli()		do{IE &= ~0x80;}while(0)
#define		sei()		do{IE |=  0x80;}while(0)
