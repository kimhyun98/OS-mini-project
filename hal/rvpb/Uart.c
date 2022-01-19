/*
 * Uart.c
 *
 *  Created on: Sep 8, 2018
 *      Author: maanu
 */

#include "stdint.h"
#include "Uart.h"
#include "HalUart.h"
#include "HalInterrupt.h"

extern volatile PL011_t* Uart;

static void interrupt_handler(void);

void Hal_uart_init(void)
{
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;
    
    Hal_interrupt_enable(UART_INTERRUPT0);
    Hal_interrupt_register_handler(interrupt_handler, UART_INTERRUPT0);
}

void Hal_uart_put_char(uint8_t ch)
{
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
}

uint8_t Hal_uart_get_char(void)
{
	uint32_t data;

	while(Uart->uartfr.bits.RXFE);

	data = Uart->uartdr.all;

	if(data & 0xFFFFFF00)
	{
		Uart->uartrsr.all = 0xFF;
		return 0;	
	}	
	return (uint8_t)(data & 0xFF);
}

void interrupt_handler(void)
{
	int8_t ch = Hal_uart_get_char(void);
	Hal_uart_put_char(ch);
}
