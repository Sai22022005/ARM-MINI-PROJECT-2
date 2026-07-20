	//AI User Activity Monitoring System Using LPC2129 with HC-05 
	
	#include<lpc21xx.h>
	#include "header.h"
	
	// Define LEDs and Switches
	#define GREEN_LED (1<<16)   // P0.16 ? Green LED (Active Low)
	#define RED_LED   (1<<17)   // P0.17 ? Red LED (Active Low)

	#define SW1 (1<<18)   // LOGIN
	#define SW2 (1<<19)   // ACTIVE
	#define SW3 (1<<20)   // STATUS
	#define SW4 (1<<21)   // LOGOUT
	
	int main(void) 
		{
			uart0_init(9600);
			lcd_init();
			lcd_string("AI USER MONITOR");
			uart0_string("System Initialized\r\n");
			
			IODIR0 |= GREEN_LED | RED_LED;   // LEDs as output
			IODIR0 &= ~(SW1 | SW2 | SW3 | SW4); // Switches as input
			IOSET0 = GREEN_LED | RED_LED;    // LEDs OFF initially (active-low)
			
while(1)
{
    char bt_cmd = 0;
    if (U0LSR & 0x01)
			{                  // Check if Bluetooth sent data
        bt_cmd = U0RBR;
			}

    if (bt_cmd == '1' || !(IOPIN0 & SW1)) // LOGIN
			{
        lcd_cmd(0xC0);
        lcd_string("LOGIN");
        uart0_string("User Logged In\r\n");
			}
    else if (bt_cmd == '2' || !(IOPIN0 & SW2))  // ACTIVE
			{
        lcd_cmd(0xC0);
        lcd_string("USER ACTIVE");
        IOCLR0 = GREEN_LED;   // Green LED ON (active-low)
        IOSET0 = RED_LED;     // Red LED OFF
        uart0_string("AI STATUS : ACTIVE\r\n");
      }
   
    else if (bt_cmd == '3' || !(IOPIN0 & SW3)) // STATUS
			{
        lcd_cmd(0xC0);
        lcd_string("STATUS CHECK");
        uart0_string("Monitoring Status\r\n");
			}
			// LOGOUT
    else if (bt_cmd == '4' || !(IOPIN0 & SW4)) // LOGOUT
			{
        lcd_cmd(0xC0);
        lcd_string("LOGOUT");
        IOCLR0 = RED_LED;     // Red LED ON
        IOSET0 = GREEN_LED;   // Green LED OFF
        uart0_string("WARNING : IDLE USER\r\n");
			}
	}
}
