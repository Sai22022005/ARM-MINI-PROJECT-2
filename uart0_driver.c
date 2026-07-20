#include <lpc21xx.h>
#include "header.h"

void uart0_init(unsigned int baud)
{
    int pclk, result = 0;

    if(VPBDIV == 0x0)
        pclk = 15000000;
    else if(VPBDIV == 0x01)
        pclk = 60000000;
    else if(VPBDIV == 0x02)
        pclk = 30000000;   

    result = pclk / (16 * baud);

    PINSEL0 |= 0x00000005;  
    U0LCR = 0x83;            
    U0DLL = (result & 0xFF);
    U0DLM = (result >> 8) & 0xFF;
    U0LCR = 0x03;            
}

#define THRE ((U0LSR >> 5) & 1)
void uart0_tx(unsigned char data)
{
    while(THRE == 0);
    U0THR = data;
}

#define RDR (U0LSR & 1)
unsigned char uart0_rx(void)
{
    while(RDR == 0);
    return U0RBR;
}

void uart0_string(char *ptr)
{
    while(*ptr != 0)
    {
        uart0_tx(*ptr++);
    }
}
