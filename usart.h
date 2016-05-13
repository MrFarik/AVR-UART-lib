#ifndef _USART_H_
#define _USART_H_

/************************************************************************************
 *  Published on: 21-02-2015                                                        *
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/

// DO NOT DEFINE BUFFERS SIZES OR ANY SHARED MACROS IN 'main.c' CODE
// instead of this, define it in "Project Properties -> AVR C Compiler -> Symbols" or try to use -D gcc flag (eg. -DF_CPU=8000000)

//#define NO_USART_RX // disable all receiver code and dependencies
//#define NO_USART_TX // disable all transmitter code and dependencies

//#define USART_RS485_MODE // globally enable rs485 operation mode // RE have to be shorted with DE
//#define USART_MPCM_MODE // globally enable MPCM operation mode // 9 bit data frame only // always set frame format to 8 data bits
//#define USART_DISABLE_TRANSMITTER_ON_TXC // especially in case of multiple slaves connected directly to each other // requires pullup resistor on master rx line

//#define USE_DOUBLE_SPEED // enables double speed for all available USART interfaces 

#define RX_STDIO_GETCHAR_ECHO // echoes back received characters in getchar() function (for reading in scanf()) 
#define RX_GETC_ECHO // echoes back received characters in getc() function

//#define PUTC_CONVERT_LF_TO_CRLF // allow for unix style (\n only) newline terminator in stored strings // not included into putc_noblock
#define RX_NEWLINE_MODE 2 // 0 - \r,  1 - \n,  2 - \r\n
// lot of terminals sends only \r character as a newline terminator, instead of \r\n or even unix style \n
// (BTW PuTTY doesn't allow to change this) but in return requires \r\n terminator to show not broken text

//#define USART_PUTC_FAST_INSERTIONS // skip FIFO procedure and write directly data to the UDR register when possible // probably required for full bus utilization at highest speed (first insertions would generate ISR worst case)
//#define USART_UNSAFE_TX_INTERRUPT // enable interrupts in TX ISR handler to meet 25 cycle restriction // safe enough to enable - ISR will not interrupt itself, only 3+PC bytes on stack 
//#define USART_UNSAFE_RX_INTERRUPT // enable interrupts in RX ISR handler to meet 25 cycle restriction // unsafe - ISR can interrupt itself after receiving another byte, only 4+PC bytes on stack 
//#define USART_UNSAFE_RX_INTERRUPT_BUFF_AWARE // modify TX interrupt to meet 33 cycle restriction // doesn't overwrite or reverse received bytes
//#define USART_NO_DIRTY_HACKS // if any bootloader uses <=4800 bps speed at 20MHz
/*****************************config for multiple USART mcu's***********************************/

//#define NO_USART0 // disable usage of uart0
//#define NO_USART1 // disable usage of uart1
//#define NO_USART2 // disable usage of uart2
//#define NO_USART3 // disable usage of uart3

//#define NO_RX0_INTERRUPT // disables interrupt handling and frees RX0 gpio port // combining with NO_USART_RX is not necessary 
//#define NO_RX1_INTERRUPT // disables interrupt handling and frees RX1 gpio port
//#define NO_RX2_INTERRUPT // disables interrupt handling and frees RX2 gpio port
//#define NO_RX3_INTERRUPT // disables interrupt handling and frees RX3 gpio port

//#define NO_TX0_INTERRUPT // disables interrupt handling and frees TX0 gpio port // combining with NO_USART_TX is not necessary
//#define NO_TX1_INTERRUPT // disables interrupt handling and frees TX1 gpio port
//#define NO_TX2_INTERRUPT // disables interrupt handling and frees TX2 gpio port
//#define NO_TX3_INTERRUPT // disables interrupt handling and frees TX3 gpio port

//#define USART0_U2X_SPEED // enables double speed for USART0
//#define USART1_U2X_SPEED // enables double speed for USART1
//#define USART2_U2X_SPEED // enables double speed for USART2
//#define USART3_U2X_SPEED // enables double speed for USART3

//#define RX0_GETC_ECHO
//#define RX1_GETC_ECHO
//#define RX2_GETC_ECHO
//#define RX3_GETC_ECHO

//#define USART0_PUTC_FAST_INSERTIONS
//#define USART1_PUTC_FAST_INSERTIONS
//#define USART2_PUTC_FAST_INSERTIONS
//#define USART3_PUTC_FAST_INSERTIONS

//#define USART0_MPCM_MODE
//#define USART1_MPCM_MODE
//#define USART2_MPCM_MODE
//#define USART3_MPCM_MODE

//#define USART0_DISABLE_TRANSMITTER_ON_TXC
//#define USART1_DISABLE_TRANSMITTER_ON_TXC
//#define USART2_DISABLE_TRANSMITTER_ON_TXC
//#define USART3_DISABLE_TRANSMITTER_ON_TXC

//#define USART0_RS485_MODE // set correct DE pin first 
//#define USART1_RS485_MODE	// set correct DE pin first 
//#define USART2_RS485_MODE	// set correct DE pin first 
//#define USART3_RS485_MODE	// set correct DE pin first 

/*****************************RS 485 config***********************************/

//#define RS485_CONTROL0_PORT D // A,B,C,D ... port naming - define valid port connected to DE + RE 
//#define RS485_CONTROL0_PIN 2 // 1,2,3,4 ... pin naming - define valid pin connected to DE + RE

//#define RS485_CONTROL1_PORT 
//#define RS485_CONTROL1_PIN 

//#define RS485_CONTROL2_PORT 
//#define RS485_CONTROL2_PIN

//#define RS485_CONTROL3_PORT
//#define RS485_CONTROL3_PIN

/*****************************MPCM config***********************************/

#define MPCM0_ADDRESS 0x01
#define MPCM1_ADDRESS 0x02
#define MPCM2_ADDRESS 0x03
#define MPCM3_ADDRESS 0x04

//#define MPCM0_GCALL_ADDRESS 0x00
//#define MPCM1_GCALL_ADDRESS 0x00
//#define MPCM2_GCALL_ADDRESS 0x00
//#define MPCM3_GCALL_ADDRESS 0x00

//#define MPCM0_MASTER_ONLY // do not include slave code into RX ISR
//#define MPCM1_MASTER_ONLY // do not include slave code into RX ISR
//#define MPCM2_MASTER_ONLY // do not include slave code into RX ISR
//#define MPCM3_MASTER_ONLY // do not include slave code into RX ISR

#include <avr/io.h> // for inline func

#ifndef F_CPU
	#error F_CPU is undefined, USART cannot work correctly without this parametr
#endif

#define BAUD_CALC(x) ((F_CPU+(x)*8UL) / (16UL*(x))-1UL) // macro calculating UBBR value
#define BAUD_CALC_FAST(x) ((F_CPU)/(BAUD*16UL)-1) // for faster real time calculations ?
#define DOUBLE_BAUD_CALC(x) ((F_CPU+(x)*4UL) / (8UL*(x))-1UL) // macro calculating UBBR value for double speed

#ifndef __OPTIMIZE__
	#warning "Compiler optimizations disabled; functions from usart.h won't work as designed"
	#define USART_NO_DIRTY_HACKS
#endif
	
#ifdef DEBUG
	#define USART_NO_DIRTY_HACKS
#endif

#ifndef RX_BUFFER_SIZE
	#define RX_BUFFER_SIZE 32 // Size of the ring buffers, must be power of 2
#endif

#ifndef TX_BUFFER_SIZE
	#define TX_BUFFER_SIZE 32 // Size of the ring buffers, must be power of 2
#endif

#ifndef TX0_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define TX0_BUFFER_SIZE TX_BUFFER_SIZE
#endif
#ifndef RX0_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define RX0_BUFFER_SIZE RX_BUFFER_SIZE
#endif
#ifndef TX1_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define TX1_BUFFER_SIZE TX_BUFFER_SIZE
#endif
#ifndef RX1_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define RX1_BUFFER_SIZE RX_BUFFER_SIZE
#endif
#ifndef TX2_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define TX2_BUFFER_SIZE TX_BUFFER_SIZE
#endif
#ifndef RX2_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define RX2_BUFFER_SIZE RX_BUFFER_SIZE
#endif
#ifndef TX3_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define TX3_BUFFER_SIZE TX_BUFFER_SIZE
#endif
#ifndef RX3_BUFFER_SIZE // Size of the ring buffers, must be power of 2
	#define RX3_BUFFER_SIZE RX_BUFFER_SIZE
#endif

#define TX0_BUFFER_MASK (TX0_BUFFER_SIZE - 1)
#define RX0_BUFFER_MASK (RX0_BUFFER_SIZE - 1)

#define TX1_BUFFER_MASK (TX1_BUFFER_SIZE - 1)
#define RX1_BUFFER_MASK (RX1_BUFFER_SIZE - 1)

#define TX2_BUFFER_MASK (TX2_BUFFER_SIZE - 1)
#define RX2_BUFFER_MASK (RX2_BUFFER_SIZE - 1)

#define TX3_BUFFER_MASK (TX3_BUFFER_SIZE - 1)
#define RX3_BUFFER_MASK (RX3_BUFFER_SIZE - 1)

enum {locked, unlocked};
enum {COMPLETED = 1, BUFFER_EMPTY = 0, BUFFER_FULL=0};
	
#if defined(URSEL)||defined(URSEL0)||defined(URSEL1)||defined(URSEL2)||defined(URSEL3)

	#define USART_XCK_RISING_EDGE 0x80
	#define USART_XCK_FALLING_EDGE 0x81

	#define USART_5BIT_DATA 0x80
	#define USART_6BIT_DATA 0x82
	#define USART_7BIT_DATA 0x84
	#define USART_8BIT_DATA 0x86

	#define USART_1STOP_BIT 0x80
	#define USART_2STOP_BITS 0x88

	#define USART_NO_PARITY 0x80
	#define USART_EVEN_PARITY 0xA0
	#define USART_ODD_PARITY 0xB0
	
	#define USART_ASYNC_MODE 0x80
	#define USART_SYNC_MODE 0xC0
#else
	#define USART_XCK_RISING_EDGE 0x00
	#define USART_XCK_FALLING_EDGE 0x01

	#define USART_5BIT_DATA 0x00
	#define USART_6BIT_DATA 0x02
	#define USART_7BIT_DATA 0x04
	#define USART_8BIT_DATA 0x06

	#define USART_1STOP_BIT 0x00
	#define USART_2STOP_BITS 0x08

	#define USART_NO_PARITY 0x00
	#define USART_EVEN_PARITY 0x20
	#define USART_ODD_PARITY 0x30
	
	#define USART_ASYNC_MODE 0x00
	#define USART_SYNC_MODE 0x40
	#define USART_MSPI_MODE 0xC0
#endif

#ifdef NO_USART_RX // remove all RX interrupts
	#define NO_RX0_INTERRUPT
	#define NO_RX1_INTERRUPT
	#define NO_RX2_INTERRUPT
	#define NO_RX3_INTERRUPT
#endif

#ifdef NO_USART_TX // remove all TX interrupts
	#define NO_TX0_INTERRUPT
	#define NO_TX1_INTERRUPT
	#define NO_TX2_INTERRUPT
	#define NO_TX3_INTERRUPT
#endif

#ifdef USE_DOUBLE_SPEED 
	#define USART0_U2X_SPEED
	#define USART1_U2X_SPEED
	#define USART2_U2X_SPEED
	#define USART3_U2X_SPEED
#endif

#ifdef RX_GETC_ECHO
	#define RX0_GETC_ECHO
	#define RX1_GETC_ECHO
	#define RX2_GETC_ECHO
	#define RX3_GETC_ECHO
#endif

#ifdef USART_PUTC_FAST_INSERTIONS
	#define USART0_PUTC_FAST_INSERTIONS
	#define USART1_PUTC_FAST_INSERTIONS
	#define USART2_PUTC_FAST_INSERTIONS
	#define USART3_PUTC_FAST_INSERTIONS
#endif

#ifdef USART_RS485_MODE
	#define USART0_RS485_MODE
	#define USART1_RS485_MODE
	#define USART2_RS485_MODE
	#define USART3_RS485_MODE
#endif

#ifdef USART_MPCM_MODE
	#define USART0_MPCM_MODE
	#define USART1_MPCM_MODE
	#define USART2_MPCM_MODE
	#define USART3_MPCM_MODE
#endif

#ifdef USART_DISABLE_TRANSMITTER_ON_TXC
	#define USART0_DISABLE_TRANSMITTER_ON_TXC
	#define USART1_DISABLE_TRANSMITTER_ON_TXC
	#define USART2_DISABLE_TRANSMITTER_ON_TXC
	#define USART3_DISABLE_TRANSMITTER_ON_TXC
#endif

#ifdef USART0_RS485_MODE
	#if !defined(RS485_CONTROL0_PORT)||!defined(RS485_CONTROL0_PIN)
		#error "define valid DE/RE output for USART0 RS485 operation"
	#endif
#endif

#ifdef USART1_RS485_MODE
	#if !defined(RS485_CONTROL1_PORT)||!defined(RS485_CONTROL1_PIN)
		#error "define valid DE/RE output for USART1 RS485 operation"
	#endif
#endif

#ifdef USART2_RS485_MODE
	#if !defined(RS485_CONTROL2_PORT)||!defined(RS485_CONTROL2_PIN)
		#error "define valid DE/RE output for USART2 RS485 operation"
	#endif
#endif

#ifdef USART3_RS485_MODE
	#if !defined(RS485_CONTROL3_PORT)||!defined(RS485_CONTROL3_PIN)
		#error "define valid DE/RE output for USART3 RS485 operation"
	#endif
#endif

#ifndef ___DDR
	#define ___DDR(x) ___XDDR(x)
#endif
#ifndef ___XDDR
	#define ___XDDR(x) (DDR ## x)
#endif

#ifndef ___PORT
	#define ___PORT(x) ___XPORT(x)
#endif
#ifndef ___XPORT
	#define ___XPORT(x) (PORT ## x)
#endif

#ifdef RX_NEWLINE_MODE
	
	#if (RX_NEWLINE_MODE == 0)
		#define RX_NEWLINE_MODE_R
	#elif (RX_NEWLINE_MODE == 1)
		#define RX_NEWLINE_MODE_N
	#else // RX_NEWLINE_MODE == 2
		#define RX_NEWLINE_MODE_RN
	#endif
#else
	#define RX_NEWLINE_MODE_RN // 2
#endif

#if defined(__usbdrv_h_included__)&&(!defined(USART_UNSAFE_RX_INTERRUPT)||!defined(USART_UNSAFE_RX_INTERRUPT_BUFF_AWARE))
	#warning "usb may not work with RX ISR's"
#endif

#if defined(__usbdrv_h_included__)&&!defined(USART_UNSAFE_TX_INTERRUPT)
	#warning "usb may not work with TX ISR's"
#endif

#if defined(__AVR_ATtiny102__)||defined(__AVR_ATtiny104__)

#if (TX0_BUFFER_SIZE > 8)||(RX0_BUFFER_SIZE > 8)
	#warning "TX or RX buffer may be too large for this device"
#endif

#define USART0_IN_IO_ADDRESS_SPACE
#define USART0_NOT_ACCESIBLE_FROM_CBI

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RXC_vect
	#define TXC0_INTERRUPT  	USART0_TXC_vect
	#define UDRE0_INTERRUPT		USART0_DRE_vect
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT   		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80
	
#endif //NO_USART0
#endif

#if defined(__AVR_ATtiny2313__)||defined(__AVR_ATtiny2313A__)||defined(__AVR_ATtiny4313)

#define USART0_IN_IO_ADDRESS_SPACE

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART_RX_vect
	#define TXC0_INTERRUPT  	USART_TX_vect
	#define UDRE0_INTERRUPT		USART_UDRE_vect
	#define UDR0_REGISTER		UDR
	#define UBRR0L_REGISTER		UBRRL
	#define UBRR0H_REGISTER		UBRRH
	#define UCSR0A_REGISTER		UCSRA
	#define UCSR0B_REGISTER		UCSRB
	#define UCSR0C_REGISTER		UCSRC
	#define TXCIE0_BIT      	TXCIE
	#define UDRIE0_BIT    		UDRIE
	#define RXCIE0_BIT  		RXCIE
	#define TXEN0_BIT   		TXEN
	#define RXEN0_BIT   		RXEN
	#define UDRE0_BIT   		UDRE
	#define U2X0_BIT    		U2X
	#define MPCM0_BIT           MPCM
	#define UCSZ02_BIT          UCSZ2
	#define TXB80_BIT           TXB8

#endif //NO_USART0
#endif

#if defined(__AVR_ATtiny1634__)

#define USART0_IN_IO_ADDRESS_SPACE
#define USART0_NOT_ACCESIBLE_FROM_CBI

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT  	USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0

#ifndef NO_USART1
#define USE_USART1

	#define RX1_INTERRUPT		USART1_RX_vect
	#define TXC1_INTERRUPT  	USART1_TX_vect
	#define UDRE1_INTERRUPT		USART1_UDRE_vect
	#define UDR1_REGISTER		UDR1
	#define UBRR1L_REGISTER		UBRR1L
	#define UBRR1H_REGISTER		UBRR1H
	#define UCSR1A_REGISTER		UCSR1A
	#define UCSR1B_REGISTER		UCSR1B
	#define UCSR1C_REGISTER		UCSR1C
	#define TXCIE1_BIT      	TXCIE1
	#define UDRIE1_BIT    		UDRIE1
	#define RXCIE1_BIT  		RXCIE1
	#define TXEN1_BIT   		TXEN1
	#define RXEN1_BIT   		RXEN1
	#define UDRE1_BIT   		UDRE1
	#define U2X1_BIT    		U2X1
	#define MPCM1_BIT           MPCM1
	#define UCSZ12_BIT          UCSZ12
	#define TXB81_BIT           TXB81

#endif //NO_USART1
#endif


#if defined(__AVR_ATtiny441__)||defined(__AVR_ATtiny841__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT  	USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0

#ifndef NO_USART1
#define USE_USART1

	#define RX1_INTERRUPT		USART1_RX_vect
	#define TXC1_INTERRUPT  	USART1_TX_vect
	#define UDRE1_INTERRUPT		USART1_UDRE_vect
	#define UDR1_REGISTER		UDR1
	#define UBRR1L_REGISTER		UBRR1L
	#define UBRR1H_REGISTER		UBRR1H
	#define UCSR1A_REGISTER		UCSR1A
	#define UCSR1B_REGISTER		UCSR1B
	#define UCSR1C_REGISTER		UCSR1C
	#define TXCIE1_BIT      	TXCIE1
	#define UDRIE1_BIT    		UDRIE1
	#define RXCIE1_BIT  		RXCIE1
	#define TXEN1_BIT   		TXEN1
	#define RXEN1_BIT   		RXEN1
	#define UDRE1_BIT   		UDRE1
	#define U2X1_BIT    		U2X1
	#define MPCM1_BIT           MPCM1
	#define UCSZ12_BIT          UCSZ12
	#define TXB81_BIT           TXB81

#endif //NO_USART1
#endif

#if defined(__AVR_ATmega48__)||defined(__AVR_ATmega48P__)||defined(__AVR_ATmega48PA__)||defined(__AVR_ATmega48PB__)\
||defined(__AVR_ATmega88__)||defined(__AVR_ATmega88P__)||defined(__AVR_ATmega88PA__)||defined(__AVR_ATmega88PB__)\
||defined(__AVR_ATmega168__)||defined(__AVR_ATmega168P__)||defined(__AVR_ATmega168PA__)||defined(__AVR_ATmega168PB__)\
||defined(__AVR_ATmega328__)||defined(__AVR_ATmega328P__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART_RX_vect
	#define TXC0_INTERRUPT  	USART_TX_vect
	#define UDRE0_INTERRUPT		USART_UDRE_vect
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT   		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80	

#endif //NO_USART0
#endif

#if defined(__AVR_ATmega328PB__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT		USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT   		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0

#ifndef NO_USART1
#define USE_USART1

	#define RX1_INTERRUPT		USART1_RX_vect
	#define TXC1_INTERRUPT  	USART1_TX_vect
	#define UDRE1_INTERRUPT		USART1_UDRE_vect
	#define UDR1_REGISTER		UDR1
	#define UBRR1L_REGISTER		UBRR1L
	#define UBRR1H_REGISTER		UBRR1H
	#define UCSR1A_REGISTER		UCSR1A
	#define UCSR1B_REGISTER		UCSR1B
	#define UCSR1C_REGISTER		UCSR1C
	#define TXCIE1_BIT      	TXCIE1
	#define UDRIE1_BIT    		UDRIE1
	#define RXCIE1_BIT   		RXCIE1
	#define TXEN1_BIT   		TXEN1
	#define RXEN1_BIT   		RXEN1
	#define UDRE1_BIT   		UDRE1
	#define U2X1_BIT    		U2X1
	#define MPCM1_BIT           MPCM1
	#define UCSZ12_BIT          UCSZ12
	#define TXB81_BIT           TXB81	

#endif //NO_USART1
#endif

#if defined(__AVR_ATmega8__)||defined(__AVR_ATmega8P__)||defined(__AVR_ATmega16__)\
||defined(__AVR_ATmega16A__)||defined(__AVR_ATmega32__)||defined(__AVR_ATmega32A__)\
||defined(__AVR_ATmega8A__)||defined(__AVR_ATmega8L__)

#define USART0_IN_IO_ADDRESS_SPACE

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART_RXC_vect
	#define TXC0_INTERRUPT		USART_TXC_vect
	#define UDRE0_INTERRUPT 	USART_UDRE_vect 
	#define UDR0_REGISTER		UDR
	#define UBRR0L_REGISTER		UBRRL
	#define UBRR0H_REGISTER		UBRRH
	#define UCSR0A_REGISTER		UCSRA
	#define UCSR0B_REGISTER		UCSRB
	#define UCSR0C_REGISTER		UCSRC
	#define TXCIE0_BIT	    	TXCIE
	#define UDRIE0_BIT    		UDRIE
	#define RXCIE0_BIT  		RXCIE
	#define TXEN0_BIT   		TXEN
	#define RXEN0_BIT   		RXEN
	#define UDRE0_BIT   		UDRE
	#define U2X0_BIT    		U2X
	#define MPCM0_BIT           MPCM
	#define UCSZ02_BIT          UCSZ2
	#define TXB80_BIT           TXB8
	
#endif //NO_USART0
#endif

#if defined(__AVR_ATmega8515__)||defined(__AVR_ATmega8515L__)

#define USART0_IN_IO_ADDRESS_SPACE

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART_RX_vect
	#define TXC0_INTERRUPT		USART_TX_vect
	#define UDRE0_INTERRUPT		USART_UDRE_vect 
	#define UDR0_REGISTER		UDR
	#define UBRR0L_REGISTER		UBRRL
	#define UBRR0H_REGISTER		UBRRH
	#define UCSR0A_REGISTER		UCSRA
	#define UCSR0B_REGISTER		UCSRB
	#define UCSR0C_REGISTER		UCSRC
	#define TXCIE0_BIT      	TXCIE
	#define UDRIE0_BIT    		UDRIE
	#define RXCIE0_BIT  		RXCIE
	#define TXEN0_BIT   		TXEN
	#define RXEN0_BIT   		RXEN
	#define UDRE0_BIT   		UDRE
	#define U2X0_BIT    		U2X
	#define MPCM0_BIT           MPCM
	#define UCSZ02_BIT          UCSZ2
	#define TXB80_BIT           TXB8

#endif //NO_USART0
#endif

#if defined(__AVR_ATmega162__)

#define USART0_IN_IO_ADDRESS_SPACE
#define USART1_IN_IO_ADDRESS_SPACE

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RXC_vect
	#define TXC0_INTERRUPT		USART0_TXC_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect 
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0

#ifndef NO_USART1
#define USE_USART1

	#define RX1_INTERRUPT		USART1_RXC_vect
	#define TXC1_INTERRUPT		USART1_TXC_vect
	#define UDRE1_INTERRUPT		USART1_UDRE_vect 
	#define UDR1_REGISTER		UDR1
	#define UBRR1L_REGISTER		UBRR1L
	#define UBRR1H_REGISTER		UBRR1H
	#define UCSR1A_REGISTER		UCSR1A
	#define UCSR1B_REGISTER		UCSR1B
	#define UCSR1C_REGISTER		UCSR1C
	#define TXCIE1_BIT      	TXCIE1
	#define UDRIE1_BIT    		UDRIE1
	#define RXCIE1_BIT  		RXCIE1
	#define TXEN1_BIT   		TXEN1
	#define RXEN1_BIT   		RXEN1
	#define UDRE1_BIT   		UDRE1
	#define U2X1_BIT    		U2X1
	#define MPCM1_BIT           MPCM1
	#define UCSZ12_BIT          UCSZ12
	#define TXB81_BIT           TXB81

#endif //NO_USART1
#endif

#if defined(__AVR_ATmega128__)||defined(__AVR_ATmega128A__)||defined(__AVR_ATmega64__)\
||defined(__AVR_ATmega64A__)
	#define USART0_IN_IO_ADDRESS_SPACE
#endif

#if defined(__AVR_ATmega644__)||defined(__AVR_ATmega644P__)||defined(__AVR_ATmega644PA__)\
||defined(__AVR_ATmega1284__)||defined(__AVR_ATmega1284P__)||defined(__AVR_ATmega128__)\
||defined(__AVR_ATmega128A__)||defined(__AVR_ATmega64__)||defined(__AVR_ATmega64A__)\
||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)||defined(__AVR_ATmega640__)\
||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)||defined(__AVR_ATmega164P__)\
||defined(__AVR_ATmega324P__)||defined(__AVR_ATmega324A__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT		USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect 
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif

#if !defined(NO_USART1) && !defined(__AVR_ATmega644__)
#define USE_USART1

	#define RX1_INTERRUPT		USART1_RX_vect
	#define TXC1_INTERRUPT		USART1_TX_vect
	#define UDRE1_INTERRUPT		USART1_UDRE_vect 
	#define UDR1_REGISTER		UDR1
	#define UBRR1L_REGISTER		UBRR1L
	#define UBRR1H_REGISTER		UBRR1H
	#define UCSR1A_REGISTER		UCSR1A
	#define UCSR1B_REGISTER		UCSR1B
	#define UCSR1C_REGISTER		UCSR1C
	#define TXCIE1_BIT      	TXCIE1
	#define UDRIE1_BIT    		UDRIE1
	#define RXCIE1_BIT  		RXCIE1
	#define TXEN1_BIT   		TXEN1
	#define RXEN1_BIT   		RXEN1
	#define UDRE1_BIT   		UDRE1
	#define U2X1_BIT    		U2X1
	#define MPCM1_BIT           MPCM1
	#define UCSZ12_BIT          UCSZ12
	#define TXB81_BIT           TXB81
	
#endif // NO_USART1 && 644

#endif

#if defined(__AVR_ATmega640__)||defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)

#ifndef NO_USART2
#define USE_USART2

	#define RX2_INTERRUPT		USART2_RX_vect
	#define TXC2_INTERRUPT		USART2_TX_vect
	#define UDRE2_INTERRUPT		USART2_UDRE_vect 
	#define UDR2_REGISTER		UDR2
	#define UBRR2L_REGISTER		UBRR2L
	#define UBRR2H_REGISTER		UBRR2H
	#define UCSR2A_REGISTER		UCSR2A
	#define UCSR2B_REGISTER		UCSR2B
	#define UCSR2C_REGISTER		UCSR2C
	#define TXCIE2_BIT      	TXCIE2
	#define UDRIE2_BIT    		UDRIE2
	#define RXCIE2_BIT  		RXCIE2
	#define TXEN2_BIT   		TXEN2
	#define RXEN2_BIT   		RXEN2
	#define UDRE2_BIT   		UDRE2
	#define U2X2_BIT    		U2X2
	#define MPCM2_BIT           MPCM2
	#define UCSZ22_BIT          UCSZ22
	#define TXB82_BIT           TXB82
	
#endif // NO_USART2

#ifndef NO_USART3
#define USE_USART3

	#define RX3_INTERRUPT		USART3_RX_vect
	#define TXC3_INTERRUPT		USART3_TX_vect
	#define UDRE3_INTERRUPT		USART3_UDRE_vect 
	#define UDR3_REGISTER		UDR3
	#define UBRR3L_REGISTER 	UBRR3L
	#define UBRR3H_REGISTER		UBRR3H
	#define UCSR3A_REGISTER		UCSR3A
	#define UCSR3B_REGISTER		UCSR3B
	#define UCSR3C_REGISTER		UCSR3C
	#define TXCIE3_BIT      	TXCIE3
	#define UDRIE3_BIT    		UDRIE3
	#define RXCIE3_BIT  		RXCIE3
	#define TXEN3_BIT   		TXEN3
	#define RXEN3_BIT   		RXEN3
	#define UDRE3_BIT   		UDRE3
	#define U2X3_BIT    		U2X3
	#define MPCM3_BIT           MPCM3
	#define UCSZ32_BIT          UCSZ32
	#define TXB83_BIT           TXB83
	
#endif // NO_USART3

#endif // 640/1280/2560 usart 2 & 3 

#if defined(__AVR_ATmega8U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega16U4__)\
||defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega32U6__)

#ifndef NO_USART0 // we will call the only usart, as an usart0
#define USE_USART0

	#define RX0_INTERRUPT		USART1_RX_vect
	#define TXC0_INTERRUPT		USART1_TX_vect
	#define UDRE0_INTERRUPT		USART1_UDRE_vect 
	#define UDR0_REGISTER		UDR1
	#define UBRR0L_REGISTER		UBRR1L
	#define UBRR0H_REGISTER		UBRR1H
	#define UCSR0A_REGISTER		UCSR1A
	#define UCSR0B_REGISTER		UCSR1B
	#define UCSR0C_REGISTER		UCSR1C
	#define TXCIE0_BIT      	TXCIE1
	#define UDRIE0_BIT    		UDRIE1
	#define RXCIE0_BIT  		RXCIE1
	#define TXEN0_BIT   		TXEN1
	#define RXEN0_BIT   		RXEN1
	#define UDRE0_BIT   		UDRE1
	#define U2X0_BIT    		U2X1
	#define MPCM0_BIT           MPCM1
	#define UCSZ02_BIT          UCSZ12
	#define TXB80_BIT           TXB81

#endif // NO_USART0
#endif

#if defined(__AVR_ATmega169A__)||defined(__AVR_ATmega169__)||defined(__AVR_ATmega169P__)||defined(__AVR_ATmega169PA__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT		USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect 
	#define UDR0_REGISTER		UDR
	#define UBRR0L_REGISTER		UBRRL
	#define UBRR0H_REGISTER		UBRRH
	#define UCSR0A_REGISTER		UCSRA
	#define UCSR0B_REGISTER		UCSRB
	#define UCSR0C_REGISTER		UCSRC
	#define TXCIE0_BIT      	TXCIE
	#define UDRIE0_BIT    		UDRIE
	#define RXCIE0_BIT  		RXCIE
	#define TXEN0_BIT   		TXEN
	#define RXEN0_BIT   		RXEN
	#define UDRE0_BIT   		UDRE
	#define U2X0_BIT    		U2X
	#define MPCM0_BIT           MPCM
	#define UCSZ02_BIT          UCSZ2
	#define TXB80_BIT           TXB8

#endif //NO_USART0
#endif

#if defined(__AVR_ATmega329__)||defined(__AVR_ATmega329P__)||defined(__AVR_ATmega329PA__)\
||defined(__AVR_ATmega329A__)||defined(__AVR_ATmega649__)||defined(__AVR_ATmega649A__)\
||defined(__AVR_ATmega649P__)||defined(__AVR_ATmega169P__)||defined(__AVR_ATmega169PA__)\
||defined(__AVR_ATmega325__)||defined(__AVR_ATmega325A__)||defined(__AVR_ATmega325P__)\
||defined(__AVR_ATmega325PA__)||defined(__AVR_ATmega645__)||defined(__AVR_ATmega645A__)\
||defined(__AVR_ATmega645P__)


#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART0_RX_vect
	#define TXC0_INTERRUPT		USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect 
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0
#endif

#if defined(__AVR_ATmega3290__)||defined(__AVR_ATmega6490__)||defined(__AVR_ATmega3290P__)\
||defined(__AVR_ATmega3290PA__)||defined(__AVR_ATmega3290A__)||defined(__AVR_ATmega6490A__)\
||defined(__AVR_ATmega6490P__)||defined(__AVR_ATmega3250__)||defined(__AVR_ATmega3250A__)\
||defined(__AVR_ATmega3250P__)||defined(__AVR_ATmega3250PA__)||defined(__AVR_ATmega6450__)\
||defined(__AVR_ATmega6450A__)||defined(__AVR_ATmega6450P__)

#ifndef NO_USART0
#define USE_USART0

	#define RX0_INTERRUPT		USART_RX_vect // wtf
	#define TXC0_INTERRUPT		USART0_TX_vect
	#define UDRE0_INTERRUPT		USART0_UDRE_vect 
	#define UDR0_REGISTER		UDR0
	#define UBRR0L_REGISTER		UBRR0L
	#define UBRR0H_REGISTER		UBRR0H
	#define UCSR0A_REGISTER		UCSR0A
	#define UCSR0B_REGISTER		UCSR0B
	#define UCSR0C_REGISTER		UCSR0C
	#define TXCIE0_BIT      	TXCIE0
	#define UDRIE0_BIT    		UDRIE0
	#define RXCIE0_BIT  		RXCIE0
	#define TXEN0_BIT   		TXEN0
	#define RXEN0_BIT   		RXEN0
	#define UDRE0_BIT   		UDRE0
	#define U2X0_BIT    		U2X0
	#define MPCM0_BIT           MPCM0
	#define UCSZ02_BIT          UCSZ02
	#define TXB80_BIT           TXB80

#endif //NO_USART0
#endif

#if !defined(USE_USART0) && !defined(USE_USART1) && !defined(USE_USART2) && !defined(USE_USART3)
	#error USART not available or unknown mcu
#endif

#ifndef USE_USART0 
	#define NO_TX0_INTERRUPT
	#define NO_RX0_INTERRUPT
#endif

#ifndef USE_USART1
	#define NO_TX1_INTERRUPT
	#define NO_RX1_INTERRUPT
#endif

#ifndef USE_USART2
	#define NO_TX2_INTERRUPT
	#define NO_RX2_INTERRUPT
#endif

#ifndef USE_USART3
	#define NO_TX3_INTERRUPT
	#define NO_RX3_INTERRUPT
#endif

#ifndef USART0_CONFIG_B // set config bytes for UCSR0B_REGISTER
	
	#ifdef USART0_MPCM_MODE
		#if defined(NO_RX0_INTERRUPT)
			#define USART0_CONFIG_B (1<<TXEN0_BIT)|(1<<UCSZ02_BIT)
		
		#elif defined(NO_TX0_INTERRUPT)
			#define USART0_CONFIG_B (1<<RXEN0_BIT)|(1<<RXCIE0_BIT)|(1<<UCSZ02_BIT)
		#else
			#ifdef USART0_RS485_MODE
				#define USART0_CONFIG_B (1<<TXEN0_BIT)|(1<<TXCIE0_BIT)|(1<<RXEN0_BIT)|(1<<RXCIE0_BIT)|(1<<UCSZ02_BIT)
			#else
				#define USART0_CONFIG_B (1<<TXEN0_BIT)|(1<<RXEN0_BIT)|(1<<RXCIE0_BIT)|(1<<UCSZ02_BIT)
			#endif
		#endif
	#else
		#if defined(NO_RX0_INTERRUPT)
			#define USART0_CONFIG_B (1<<TXEN0_BIT)
		
		#elif defined(NO_TX0_INTERRUPT)
			#define USART0_CONFIG_B (1<<RXEN0_BIT)|(1<<RXCIE0_BIT)
		#else
			#ifdef USART0_RS485_MODE
				#define USART0_CONFIG_B (1<<TXEN0_BIT)|(1<<TXCIE0_BIT)|(1<<RXEN0_BIT)|(1<<RXCIE0_BIT)
			#else
				#define USART0_CONFIG_B (1<<TXEN0_BIT)|(1<<RXEN0_BIT)|(1<<RXCIE0_BIT)
			#endif
		#endif
	#endif
#endif // USART0_CONFIG

#ifndef USART1_CONFIG_B // set config bytes for UCSR1B_REGISTER
	
	#ifdef USART1_MPCM_MODE
		#if defined(NO_RX1_INTERRUPT)
			#define USART1_CONFIG_B (1<<TXEN1_BIT)|(1<<UCSZ12_BIT)
	
		#elif defined(NO_TX1_INTERRUPT)
			#define USART1_CONFIG_B (1<<RXEN1_BIT)|(1<<RXCIE1_BIT)|(1<<UCSZ12_BIT)
		#else
			#ifdef USART1_RS485_MODE
				#define USART1_CONFIG_B (1<<TXEN1_BIT)|(1<<TXCIE1_BIT)|(1<<RXEN1_BIT)|(1<<RXCIE1_BIT)|(1<<UCSZ12_BIT)
			#else
				#define USART1_CONFIG_B (1<<TXEN1_BIT)|(1<<RXEN1_BIT)|(1<<RXCIE1_BIT)|(1<<UCSZ12_BIT)
			#endif
		#endif
	#else
		#if defined(NO_RX1_INTERRUPT)
			#define USART1_CONFIG_B (1<<TXEN1_BIT)

		#elif defined(NO_TX1_INTERRUPT)
			#define USART1_CONFIG_B (1<<RXEN1_BIT)|(1<<RXCIE1_BIT)
		#else
			#ifdef USART1_RS485_MODE
				#define USART1_CONFIG_B (1<<TXEN1_BIT)|(1<<TXCIE1_BIT)|(1<<RXEN1_BIT)|(1<<RXCIE1_BIT)
			#else
				#define USART1_CONFIG_B (1<<TXEN1_BIT)|(1<<RXEN1_BIT)|(1<<RXCIE1_BIT)
			#endif
		#endif
	#endif
#endif // USART1_CONFIG

#ifndef USART2_CONFIG_B // set config bytes for UCSR2B_REGISTER

	#ifdef USART2_MPCM_MODE
		#if defined(NO_RX2_INTERRUPT)
			#define USART2_CONFIG_B (1<<TXEN2_BIT)|(1<<UCSZ22_BIT)
	
		#elif defined(NO_TX2_INTERRUPT)
			#define USART2_CONFIG_B (1<<RXEN2_BIT)|(1<<RXCIE2_BIT)|(1<<UCSZ22_BIT)
		#else
			#ifdef USART2_RS485_MODE
				#define USART2_CONFIG_B (1<<TXEN2_BIT)|(1<<TXCIE2_BIT)|(1<<RXEN2_BIT)|(1<<RXCIE2_BIT)|(1<<UCSZ22_BIT)
			#else
				#define USART2_CONFIG_B (1<<TXEN2_BIT)|(1<<RXEN2_BIT)|(1<<RXCIE2_BIT)|(1<<UCSZ22_BIT)
			#endif
		#endif
	#else
		#if defined(NO_RX2_INTERRUPT)
			#define USART2_CONFIG_B (1<<TXEN2_BIT)

		#elif defined(NO_TX2_INTERRUPT)
			#define USART2_CONFIG_B (1<<RXEN2_BIT)|(1<<RXCIE2_BIT)
		#else
			#ifdef USART2_RS485_MODE
				#define USART2_CONFIG_B (1<<TXEN2_BIT)|(1<<TXCIE2_BIT)|(1<<RXEN2_BIT)|(1<<RXCIE2_BIT)
			#else	
				#define USART2_CONFIG_B (1<<TXEN2_BIT)|(1<<RXEN2_BIT)|(1<<RXCIE2_BIT)
			#endif
		#endif
	#endif
#endif // USART2_CONFIG

#ifndef USART3_CONFIG_B // set config bytes for UCSR3B_REGISTER

	#ifdef USART3_MPCM_MODE
		#if defined(NO_RX3_INTERRUPT)
			#define USART3_CONFIG_B (1<<TXEN3_BIT)|(1<<UCSZ32_BIT)
	
		#elif defined(NO_TX3_INTERRUPT)
			#define USART3_CONFIG_B (1<<RXEN3_BIT)|(1<<RXCIE3_BIT)|(1<<UCSZ32_BIT)
		#else
			#ifdef USART3_RS485_MODE
				#define USART3_CONFIG_B (1<<TXEN3_BIT)|(1<<TXCIE3_BIT)|(1<<RXEN3_BIT)|(1<<RXCIE3_BIT)|(1<<UCSZ32_BIT)
			#else
				#define USART3_CONFIG_B (1<<TXEN3_BIT)|(1<<RXEN3_BIT)|(1<<RXCIE3_BIT)|(1<<UCSZ32_BIT)
			#endif
		#endif
	#else	
		#if defined(NO_RX3_INTERRUPT)
			#define USART3_CONFIG_B (1<<TXEN3_BIT)
		
		#elif defined(NO_TX3_INTERRUPT)
			#define USART3_CONFIG_B (1<<RXEN3_BIT)|(1<<RXCIE3_BIT)
		#else
			#ifdef USART3_RS485_MODE
				#define USART3_CONFIG_B (1<<TXEN3_BIT)|(1<<TXCIE3_BIT)|(1<<RXEN3_BIT)|(1<<RXCIE3_BIT)
			#else
				#define USART3_CONFIG_B (1<<TXEN3_BIT)|(1<<RXEN3_BIT)|(1<<RXCIE3_BIT)
			#endif
		#endif
	#endif
#endif // USART3_CONFIG

/************************************************************************************
 *                            Initializers                                          *
 ************************************************************************************/
#if defined(USE_USART1)||defined(USE_USART2)||defined(USE_USART3)
	
	// functions smaller then calling routines or executed once are inline for reducing
	// flash memory usage (eg. switch and if routines can be executed during compilation)

	void uart_reinit(uint8_t usartct, uint16_t ubbr_value); // for runtime reinitialization of uart module 

	static inline void uart_init(uint8_t usartct, uint16_t ubbr_value) // have to be called once at startup with parameters known during compilation
	{
		switch(usartct)
		{
			default:
		#ifdef USE_USART0
			case 0:
			{
			#ifdef USART0_RS485_MODE
				___DDR(RS485_CONTROL0_PORT) |= (1<<RS485_CONTROL0_PIN); // default pin state is low
			#endif	
				UBRR0L_REGISTER = (uint8_t) ubbr_value;
			
			#ifndef USART_NO_DIRTY_HACKS
				if((ubbr_value>>8) != 0) // requires -Os flag - do not use in non-inline functions
			#endif
					UBRR0H_REGISTER = (ubbr_value>>8);
			
			#ifdef USART0_U2X_SPEED
				#ifdef USART0_MPCM_MODE
					UCSR0A_REGISTER = (1<<U2X0_BIT)|(1<<MPCM0_BIT);
				#else
					UCSR0A_REGISTER = (1<<U2X0_BIT); // enable double speed
				#endif
			#elif defined(USART0_MPCM_MODE)
			
				UCSR0A_REGISTER |= (1<<MPCM0_BIT);
			#endif
			
				UCSR0B_REGISTER = USART0_CONFIG_B;
				// 8n1 is set by default, setting UCSRC is not needed
			
				break;
			}
		#endif // NO_USART0
		#ifdef USE_USART1
			case 1:
			{
			#ifdef USART1_RS485_MODE
				___DDR(RS485_CONTROL1_PORT) |= (1<<RS485_CONTROL1_PIN); // default pin state is low
			#endif
				UBRR1L_REGISTER = (uint8_t) ubbr_value;
			
			#ifndef USART_NO_DIRTY_HACKS
				if((ubbr_value>>8) != 0) // requires -Os flag - do not use in non-inline functions
			#endif
					UBRR1H_REGISTER = (ubbr_value>>8);
			
			#ifdef USART1_U2X_SPEED
				#ifdef USART1_MPCM_MODE
					UCSR1A_REGISTER = (1<<U2X1_BIT)|(1<<MPCM1_BIT);
				#else
					UCSR1A_REGISTER = (1<<U2X1_BIT); // enable double speed
				#endif
			#elif defined(USART1_MPCM_MODE)
			
				UCSR1A_REGISTER |= (1<<MPCM1_BIT);
			#endif
			
				UCSR1B_REGISTER = USART1_CONFIG_B;
				// 8n1 is set by default, setting UCSRC is not needed
			
				break;
			}
		#endif // USE_USART1
		#ifdef USE_USART2
			case 2:
			{
			#ifdef USART2_RS485_MODE
				___DDR(RS485_CONTROL2_PORT) |= (1<<RS485_CONTROL2_PIN); // default pin state is low
			#endif
				UBRR2L_REGISTER = (uint8_t) ubbr_value;
			
			#ifndef USART_NO_DIRTY_HACKS
				if((ubbr_value>>8) != 0) // requires -Os flag - do not use in non-inline functions
			#endif
					UBRR2H_REGISTER = (ubbr_value>>8);
			
			#ifdef USART2_U2X_SPEED
				#ifdef USART2_MPCM_MODE
					UCSR2A_REGISTER = (1<<U2X2_BIT)|(1<<MPCM2_BIT);
				#else
					UCSR2A_REGISTER = (1<<U2X2_BIT); // enable double speed
				#endif
			#elif defined(USART2_MPCM_MODE)
			
				UCSR2A_REGISTER |= (1<<MPCM2_BIT);
			#endif
			
				UCSR2B_REGISTER = USART2_CONFIG_B;
				// 8n1 is set by default, setting UCSRC is not needed
			
				break;
			}
		#endif // USE_USART2
		#ifdef USE_USART3
			case 3:
			{
			#ifdef USART3_RS485_MODE
				___DDR(RS485_CONTROL3_PORT) |= (1<<RS485_CONTROL3_PIN); // default pin state is low
			#endif
				UBRR3L_REGISTER = (uint8_t) ubbr_value;
			
			#ifndef USART_NO_DIRTY_HACKS
				if((ubbr_value>>8) != 0) // requires -Os flag - do not use in non-inline functions
			#endif
					UBRR3H_REGISTER = (ubbr_value>>8);
			
			#ifdef USART3_U2X_SPEED
				#ifdef USART3_MPCM_MODE
					UCSR3A_REGISTER = (1<<U2X3_BIT)|(1<<MPCM3_BIT);
				#else
					UCSR3A_REGISTER = (1<<U2X3_BIT); // enable double speed
				#endif
			#elif defined(USART3_MPCM_MODE)
			
			UCSR3A_REGISTER |= (1<<MPCM3_BIT);
			#endif
			
				UCSR3B_REGISTER = USART3_CONFIG_B;
				// 8n1 is set by default, setting UCSRC is not needed
			
				//break;
			}
		#endif // USE_USART3
		}
	}
	
	// UCSRC_reg can be used to set other than 8n1 transmission
	static inline void uart_set_FrameFormat(uint8_t usartct, uint8_t UCSRC_reg)
	{
		switch(usartct)
		{
			default:
		#ifdef USE_USART0
			case 0: UCSR0C_REGISTER = UCSRC_reg; break;
		#endif // USE_USART0
		#ifdef USE_USART1
			case 1: UCSR1C_REGISTER = UCSRC_reg; break;
		#endif // USE_USART1
		#ifdef USE_USART2
			case 2: UCSR2C_REGISTER = UCSRC_reg; break;
		#endif // USE_USART2
		#ifdef USE_USART3
			case 3: UCSR3C_REGISTER = UCSRC_reg; //break;
		#endif // USE_USART3
		}
	}
	
	static inline void uart_set_U2X(uint8_t usartct) // use instead of USE_U2Xn_SPEED
	{
		switch(usartct)
		{
			default:
		#ifdef USE_USART0
			case 0: UCSR0A_REGISTER = (1<<U2X0_BIT); break;
		#endif // USE_USART0
		#ifdef USE_USART1
			case 1: UCSR1A_REGISTER = (1<<U2X1_BIT); break;
		#endif // USE_USART1
		#ifdef USE_USART2
			case 2: UCSR2A_REGISTER = (1<<U2X2_BIT); break;
		#endif // USE_USART2
		#ifdef USE_USART3
			case 3: UCSR3A_REGISTER = (1<<U2X3_BIT); //break;
		#endif // USE_USART3
		}
	}
	
#ifdef USART0_MPCM_MODE
	void uart_mpcm_transmit_addres_Frame(uint8_t usartct, uint8_t dat);
	void uart_mpcm_slave_return_idle(uint8_t usartct) // return slave to mpcm idle mode (wait for own addres frame)
	{
		switch(usartct)
		{
			default:
		#if defined(USE_USART0)&&defined(USART0_MPCM_MODE)
			case 0: UCSR0A_REGISTER |= (1<<MPCM0_BIT); break;
		#endif // mpcm0
		#if defined(USE_USART1)&&defined(USART1_MPCM_MODE)
			case 1: UCSR1A_REGISTER |= (1<<MPCM1_BIT); break;
		#endif // mpcm1
		#if defined(USE_USART2)&&defined(USART2_MPCM_MODE)
			case 2: UCSR2A_REGISTER |= (1<<MPCM2_BIT); break;
		#endif // mpcm2
		#if defined(USE_USART3)&&defined(USART3_MPCM_MODE)
			case 3: UCSR3A_REGISTER |= (1<<MPCM3_BIT); //break;
		#endif // mpcm3
		}
	}
#endif
	
#else // single USART mcu
	
	// functions smaller then calling routines or executed once are inline for reducing 
	// flash memory usage (eg. switch and if routines can be executed during compilation)
	
	void uart_reinit(uint16_t ubbr_value); // for runtime reinitialization of uart module 
	
	static inline void uart_init(uint16_t ubbr_value) // have to be called once at startup with parameters known during compilation
	{
	#ifdef USART0_RS485_MODE
		___DDR(RS485_CONTROL0_PORT) |= (1<<RS485_CONTROL0_PIN); // default pin state is low
	#endif
		
		UBRR0L_REGISTER = (uint8_t) ubbr_value;
		
	#ifndef USART_NO_DIRTY_HACKS
		if(((ubbr_value>>8) != 0)) // requires -Os flag - do not use in non-inline functions
	#endif
			UBRR0H_REGISTER = (ubbr_value>>8);
		
	#ifdef USART0_U2X_SPEED
		#ifdef USART0_MPCM_MODE
			UCSR0A_REGISTER = (1<<U2X0_BIT)|(1<<MPCM0_BIT);
		#else
			UCSR0A_REGISTER = (1<<U2X0_BIT); // enable double speed
		#endif
	#elif defined(USART0_MPCM_MODE)
		
		UCSR0A_REGISTER |= (1<<MPCM0_BIT);
	#endif
		
		UCSR0B_REGISTER = USART0_CONFIG_B;
		// 8n1 is set by default, setting UCSRC is not needed
	}

	// UCSRC_reg can be used to set other than 8n1 transmission
	static inline void uart_set_FrameFormat(uint8_t UCSRC_reg) 
	{
		UCSR0C_REGISTER = UCSRC_reg;
	} 
	
	static inline void uart_set_U2X(void) // use instead of USE_DOUBLE_SPEED 
	{
		UCSR0A_REGISTER |= (1<<U2X0_BIT);
	} 

#ifdef USART0_MPCM_MODE
	void uart_mpcm_transmit_addres_Frame(uint8_t dat);
	void uart_mpcm_slave_return_idle(void) // return slave to mpcm idle mode (wait for own addres frame)
	{
		UCSR0A_REGISTER |= (1<<MPCM0_BIT);
	}
#endif

#endif // single/multi USART
	
/************************************************************************************
 *                          Transmitter functions                                   *
 ************************************************************************************/
#ifndef NO_USART_TX

#if defined(USE_USART1)||defined(USE_USART2)||defined(USE_USART3)
	
	void uart_putc(uint8_t usartct, char data); // put character/data into transmitter ring buffer
	uint8_t uart_putc_noblock(uint8_t usartct, char data); // returns BUFFER_FULL (false) if buffer is full and character cannot be sent at the moment
	
	void uart_putstrl(uint8_t usartct, char *string, uint8_t BytesToWrite); // in case of bascom users or buffers without NULL byte ending
	void uart_putstr(uint8_t usartct, char *string); // send string from the memory buffer 
	// stops when NULL byte is hit (NULL byte is not included into transmission)
	
	// for deprecated usage only (wastes ram data memory to keep all string constants), instead of this try to use puts_P
	#ifdef __cplusplus
		#define uart_puts(_usartct,str) uart_putstr(_usartct,(const char*)(str))// macro to avoid const char* conversion restrictions 
	#else
		#define uart_puts(_usartct,str) uart_putstr(_usartct,str)
	#endif
		
	void uart_puts_p(uint8_t usartct, const char *string); // send string from flash memory 
		#define uart_puts_P(_usartct,__s)    uart_puts_p(_usartct,PSTR(__s)) 
		// macro to automatically put a string constant into flash
	
	void uart_putint(uint8_t usartct, int16_t data);
	void uart_putintr(uint8_t usartct, int16_t data, uint8_t radix);
	
	void uart_putuint(uint8_t usartct, uint16_t data);
	void uart_putuintr(uint8_t usartct, uint16_t data, uint8_t radix);
	
	void uart_puthex(uint8_t usartct, uint8_t data);
	
	void uart_putlong(uint8_t usartct, int32_t data);
	void uart_putlongr(uint8_t usartct, int32_t data, uint8_t radix);
	
	void uart_putulong(uint8_t usartct, uint32_t data);
	void uart_putulongr(uint8_t usartct, uint32_t data, uint8_t radix);
	
	void uart_putfloat(uint8_t usartct, float data);
	void uart_fputfloat(uint8_t usartct, float data, uint8_t precision);
	
	void uart_flush(uint8_t usartct); // flush tx buffer

#else // single USART mcu

	void uart_putc(char data); // put character/data into transmitter ring buffer
	uint8_t uart_putc_noblock(char data); // returns BUFFER_FULL (false) if buffer is full and character cannot be sent at the moment
	
	void uart_putstrl(char *string, uint8_t BytesToWrite); // in case of bascom users or buffers without NULL byte ending
	void uart_putstr(char *string); // send string from the memory buffer
		// stops when NULL byte is hit (NULL byte is not included into transmission)
	#ifdef __cplusplus
		#define uart_puts(str) uart_putstr((const char*)(str))// macro to avoid const char* conversion restrictions
	#else
		#define uart_puts(str) uart_putstr(str)
	#endif
		// for deprecated usage only (wastes SRAM data memory to keep all string constants), instead of this try to use puts_P

	void uart_puts_p(const char *string); // send string from flash memory
		#define uart_puts_P(__s)    uart_puts_p(PSTR(__s))
		// macro to automatically put a string constant into flash
	
	void uart_putint(int16_t data);
	void uart_putintr(int16_t data, uint8_t radix);

	void uart_putuint(uint16_t data);
	void uart_putuintr(uint16_t data, uint8_t radix);
	
	void uart_puthex(uint8_t data);

	void uart_putlong(int32_t data);
	void uart_putlongr(int32_t data, uint8_t radix);

	void uart_putulong(uint32_t data);
	void uart_putulongr(uint32_t data, uint8_t radix);
	
	void uart_putfloat(float data);
	void uart_fputfloat(float data, uint8_t precision);
	
	void uart_flush(void); // flush tx buffer

#endif // single/multi USART

#endif // NO_USART_TX

/************************************************************************************
 *                           Receiver functions                                     *
 ************************************************************************************/
#ifndef NO_USART_RX

#if defined(USE_USART1)||defined(USE_USART2)||defined(USE_USART3)
	
	char uart_getc(uint8_t usartct); // get character from receiver ring buffer
	
	void uart_gets(uint8_t usartct, char *buffer, uint8_t bufferlimit); // reads whole receiver buffer or bufferlimit-1 characters
	// newline terminator will not be cut // adds NULL byte at the end of string
	void uart_getln(uint8_t usartct, char *buffer, uint8_t bufferlimit); // reads one line from the buffer, 
	// waits for newline terminator or reached bufferlimit // adds NULL byte at the end of string
	void uart_getlnToFirstWhiteSpace(uint8_t usartct, char *buffer, uint8_t bufferlimit); // read one line to the first whitespace after the string
	//cuts all whitespaces before string and one after the string
	
	char uart_skipWhiteSpaces(uint8_t usartct); // returns first nonspace character found in the buffer
	
	int16_t uart_getint(uint8_t usartct);
	int32_t uart_getlong(uint8_t usartct);
	float uart_getfloat(uint8_t usartct);
	
	uint8_t uart_getData(uint8_t usartct, uint8_t *data); // reads binary data from a buffer and loads it into *data byte 
	// in case of empty buffers returned flag is set to BUFFER_EMPTY - NULL
	uint8_t uart_AvailableBytes(uint8_t usartct); // returns number of bytes waiting in the receiver buffer
	uint8_t uart_peek(uint8_t usartct); // returns next byte from buffer // returned byte is invalid if there is nothing to read

#else // single USART mcu

	char uart_getc(void); // get character from receiver ring buffer
	
	void uart_gets(char *buffer, uint8_t bufferlimit); // reads whole receiver buffer or bufferlimit-1 characters
	// newline terminator will not be cut // adds NULL byte at the end of string
	void uart_getln(char *buffer, uint8_t bufferlimit); // reads one line from the buffer
	// waits for newline terminator or reached bufferlimit // adds NULL byte at the end of string
	void uart_getlnToFirstWhiteSpace(char *buffer, uint8_t bufferlimit); // read one line to the first whitespace after the string
	// cuts all whitespaces before string and one after the string
	
	char uart_skipWhiteSpaces(void); // returns first nonspace character found in the buffer
	
	int16_t uart_getint(void);
	int32_t uart_getlong(void);
	float uart_getfloat(void);
	
	uint8_t uart_getData(uint8_t *data); // reads binary data from a buffer and loads it into *data byte
	// in case of empty buffers returning flag is set to BUFFER_EMPTY - NULL
	uint8_t uart_AvailableBytes(void); // returns number of bytes waiting in the receiver buffer
	uint8_t uart_peek(void); // returns next byte from buffer // returned byte is invalid if there is nothing to read

#endif // single/multi USART

#endif // NO_USART_RX

/************************************************************************************
 *                           stdio.h stuff                                          *
 ************************************************************************************/
#include <stdio.h> // avoid compilation errors

#if defined(USE_USART1)||defined(USE_USART2)||defined(USE_USART3)

	// wrapper of stdio.h FDEV_SETUP_STREAM to allow setting udata; udata is used to store info about port ID
	#define FDEV_SETUP_STREAM_U(p, g, f, u) \
	{ \
		.put = p, \
		.get = g, \
		.flags = f, \
		.udata = u, \
	}
	
	#ifndef NO_USART_TX
		void uart_putchar(char data, FILE *stream);
	#endif

	#ifndef NO_USART_RX
		char uart_getchar(FILE *stream);
	#endif
	
	#ifdef USE_USART0
	
		#if defined(NO_RX0_INTERRUPT)
			extern FILE uart0_out;
		
		#elif defined(NO_TX0_INTERRUPT)
			extern FILE uart0_in;
		#else
			extern FILE uart0_io;
		#endif
		
	#endif // USE_USART0
	
	#ifdef USE_USART1
	
		#if defined(NO_RX1_INTERRUPT)
			extern FILE uart1_out;
		
		#elif defined(NO_TX1_INTERRUPT)
			extern FILE uart1_in;
		#else
			extern FILE uart1_io;
		#endif
		
	#endif // USE_USART1
	
	#ifdef USE_USART2
	
		#if defined(NO_RX2_INTERRUPT)
			extern FILE uart2_out;
		
		#elif defined(NO_TX2_INTERRUPT)
			extern FILE uart2_in;
		#else
			extern FILE uart2_io;
		#endif
		
	#endif // USE_USART2
		
	#ifdef USE_USART3
		
		#if defined(NO_RX3_INTERRUPT)
			extern FILE uart3_out;
		
		#elif defined(NO_TX3_INTERRUPT)
			extern FILE uart3_in;
		#else
			extern FILE uart3_io;
		#endif
		
	#endif // USE_USART3
	
#else // single USART mcu

	#ifndef NO_TX0_INTERRUPT
		void uart_putchar(char data, FILE *stream);
	#endif

	#ifndef NO_RX0_INTERRUPT
		char uart_getchar(FILE *stream);
	#endif
	
	#if defined(NO_RX0_INTERRUPT)
		extern FILE uart0_out;
	
	#elif defined(NO_TX0_INTERRUPT)
		extern FILE uart0_in;
	#else
		extern FILE uart0_io;
	#endif
	
#endif // single/multi USART


#endif // _USART_H_

// if any other uart library produces better code than this, you can contact me to fix this issue