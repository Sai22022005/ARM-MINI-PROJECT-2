#include<lpc21xx.h>
#include"header.h"
void lcd_data(unsigned char data)
{
    unsigned int temp;

    // HIGHER NIBBLE
    IOCLR1 = 0xFF << 16;                
		temp = (data & 0xF0) << 16;          
    IOSET1 = temp;
    IOSET1 = 1<<17;                      
    IOCLR1 = 1<<18;                     
    IOSET1 = 1<<19;                      
    delay_ms(2);
    IOCLR1 = 1<<19;                      

    // LOWER NIBBLE
    IOCLR1 = 0xFF << 16;
    temp = (data & 0x0F) << 20;          
		IOSET1 = temp;
    IOSET1 = 1<<17;
    IOCLR1 = 1<<18;
    IOSET1 = 1<<19;
    delay_ms(2);
    IOCLR1 = 1<<19;
}

void lcd_cmd(unsigned char cmd)
{
    unsigned int temp;

    // HIGHER NIBBLE
    IOCLR1 = 0xFF << 16;
    temp = (cmd & 0xF0) << 16;
    IOSET1 = temp;
    IOCLR1 = 1<<17;                      
    IOCLR1 = 1<<18;                      
    IOSET1 = 1<<19;
    delay_ms(2);
    IOCLR1 = 1<<19;

    // LOWER NIBBLE
    IOCLR1 = 0xFF << 16;
    temp = (cmd & 0x0F) << 20;
    IOSET1 = temp;
    IOCLR1 = 1<<17;
    IOCLR1 = 1<<18;
    IOSET1 = 1<<19;
    delay_ms(2);
    IOCLR1 = 1<<19;
}

void lcd_init(void)
{
    IODIR1 |= 0xFF << 16; 
    PINSEL1 = 0x0;

    lcd_cmd(0x02);  
    lcd_cmd(0x28);  
    lcd_cmd(0x0E); 
    lcd_cmd(0x01);  
}

void lcd_string(char *ptr)
{
    while(*ptr != 0)
    {
        lcd_data(*ptr++);
    }
}
