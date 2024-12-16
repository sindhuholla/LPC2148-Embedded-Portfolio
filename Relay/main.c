
/*
This program switches relay on and off with certain delay
*/
/*************************************************

Submission Details:
Name: Sindhu Holla
File: Relay Interfacing with LPC2148

Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
P0.0 -> Relay

**************************************************/


#include <lpc214x.h>
#include "Timer.h"
#include "PLL.h"

#define bit(x) (1 << x)

int main(void) {
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
	
    // Set pin 0.0 as output
    IO0DIR |= bit(0);

    // Initial state of the pin
    IO0CLR = bit(0);
	
	
    while (1) {
        // Turn relay ON
        IO0SET = bit(0);
        delay(500);
        
        // Turn relay OFF
        IO0CLR = bit(0);
        delay(500);
    }

    return 0; // This line will never be reached
}
