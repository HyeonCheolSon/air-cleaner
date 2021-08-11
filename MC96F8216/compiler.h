/** \file compiler.h
  * \author Maarten Brock
  *
  * This library is free software; you can redistribute it and/or
  * modify it under the terms of the GNU Lesser General Public
  * License as published by the Free Software Foundation; either
  * version 2.1 of the License, or (at your option) any later version.
  *
  * This library is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  * Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public
  * License along with this library; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
  *
  * In other words, you are welcome to use, share and improve this program.
  * You are forbidden to forbid anyone else to use, share and improve
  * what you give them. Help stamp out software-hoarding!
  *
  * Header file to overcome 8051 compiler differences for specifying
  * special function registers. The following compilers are supported:
  * SDCC, Keil, Raisonance, IAR, Hi-Tech, Tasking, Crossware, Wickenhaeuser.
  * Unfortunately not for use with Dunfield. The compilers are identified by
  * their unique predefined macros. See also:
  * http://predef.sourceforge.net/precomp.html
  *
  * SBIT and SFR define special bit and special function registers at the given
  * address. SFR16 and SFR32 define sfr combinations at adjacent addresses in
  * little-endian format. SFR16E and SFR32E define sfr combinations without
  * prerequisite byte order or adjacency. None of these multi-byte sfr
  * combinations will guarantee the order in which they are accessed when read
  * or written.
  * SFR16X and SFR32X for 16 bit and 32 bit xdata registers are not defined
  * to avoid portability issues because of compiler endianness.
  * This file is to be included in every microcontroller specific header file.
  * Example:
  *
  * // my_mcu.h: sfr definitions for my mcu
  * #include <compiler.h>
  *
  * SBIT  (P0_1, 0x80, 1);      // Port 0 pin 1
  *
  * SFR   (P0, 0x80);           // Port 0
  *
  * SFRX  (CPUCS, 0xE600);      // Cypress FX2 Control and Status register in xdata memory at 0xE600
  *
  * SFR16 (TMR2, 0xCC);         // Timer 2, lsb at 0xCC, msb at 0xCD
  *
  * SFR16E(TMR0, 0x8C8A);       // Timer 0, lsb at 0x8A, msb at 0x8C
  *
  * SFR32 (MAC0ACC, 0x93);      // SiLabs C8051F120 32 bits MAC0 Accumulator, lsb at 0x93, msb at 0x96
  *
  * SFR32E(SUMR, 0xE5E4E3E2);   // TI MSC1210 SUMR 32 bits Summation register, lsb at 0xE2, msb at 0xE5
  *
//-------------------------------------------------------------------------
  * changed xdata definitions	// ABOV Semiconductor	2021. 3.25.Thu
	SFRX() is defined as	: volatile unsigned char
	if 2 or more source files include this header, it generates "double definition" error.
	--> So, it should be defined as static to avoid conflict
//-------------------------------------------------------------------------
 */

#ifndef COMPILER_H
#define COMPILER_H

/** IAR 8051
  * http://www.iar.com
 */
#if defined __ICC8051__
#include <stdbool.h>
# define SBIT(name, addr, bit)  __bit __no_init volatile bool name @ (addr+bit)
# define SFR(name, addr)        __sfr __no_init volatile unsigned char name @ addr
# define SFRX(name, addr)       __xdata __no_init static volatile unsigned char name @ addr
# define SFR16(name, addr)      __sfr __no_init volatile unsigned int  name @ addr
# define SFR16E(name, fulladdr) /* not supported */
# define SFR32(name, fulladdr)  __sfr __no_init volatile unsigned long name @ addr
# define SFR32E(name, fulladdr) /* not supported */

/** Keil C51
  * http://www.keil.com
 */
#else
# define SBIT(name, addr, bit)  sbit  name = addr^bit
# define SFR(name, addr)        sfr   name = addr
# define SFRX(name, addr)       static volatile unsigned char xdata name _at_ addr
# define SFR16(name, addr)      sfr16 name = addr
# define SFR16E(name, fulladdr) /* not supported */
# define SFR32(name, fulladdr)  /* not supported */
# define SFR32E(name, fulladdr) /* not supported */

#endif

#endif //COMPILER_H
