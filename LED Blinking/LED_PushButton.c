/*
This program turns on the LED based on the press of Push Button.
1st Press -> 1st LED
2nd Press -> 2nd LED
3rd Press -> 3rd LED
*/
/**************************************************************************************************
Name      : Sindhu Holla
Reg No    : 241039004
Board 		: LPC2148
		
Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
P0.6 - LED 1
P0.7 - LED 2
P0.8 - LED 3
P0.9 - PUSH BUTTON
	       
********************************************************************************/
#include <lpc214x.h>
#include "Timer.h"
#include "PLL.h"


int main(void)
{
    unsigned int press_count = 0; // Initialize a counter to keep track of the number of presses
    unsigned int led_num = 1; // Initialize the variable to control which LED to blink
		
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
	
    // Configure P0.6, P0.7, and P0.8 as Output (LED control)
    IO0DIR |= (1 << 6) | (1 << 7) | (1 << 8);

    // Configure P0.9 as Input (Switch input)
    IO0DIR &= ~(1 << 9);

    while(1)
    {
        // Read the state of P0.9
        if (!(IO0PIN & (1 << 9))) // Switch pressed (assuming active low)
        {
            press_count++; // Increment the press count
            while (!(IO0PIN & (1 << 9))); // Wait for the switch to be released
        }

        switch (press_count)
        {
            case 1:
                IO0SET = (1 << 6); // Turn LED 1 ON
                delay(100); // Delay to keep LED ON
                IO0CLR = (1 << 6); // Turn LED 1 OFF
                break;
            case 2:
                IO0SET = (1 << 7); // Turn LED 2 ON
                delay(100); // Delay to keep LED ON
                IO0CLR = (1 << 7); // Turn LED 2 OFF
                break;
            case 3:
                IO0SET = (1 << 8); // Turn LED 3 ON
                delay(100); // Delay to keep LED ON
                IO0CLR = (1 << 8); // Turn LED 3 OFF
                break;
            default:
                press_count = 0; // Reset the press count
                break;
        }
    }
    return 0; // Add a return statement at the end of main()
}
