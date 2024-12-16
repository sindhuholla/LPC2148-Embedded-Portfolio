/*
This program generates square wave
*/
/****************************************************

Submission Details:
Name: Sindhu Holla
File: Square wave generator

Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
P0.25 -> Oscilloscope (A)

*****************************************************/


#include "header.h"   // Include the header file with function declarations
#include "Timer.h"
#include "PLL.h"

int main() {
    // Initialize DAC
    initDAC();
	
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
    
    while (1) {
        // Generate high level (max DAC value)
        DACR = 0x3FF << 6; // Max DAC value (1023) shifted to match DACR format
        delay(1);       // Half-period of the square wave
        
        // Generate low level (min DAC value)
        DACR = 0x000 << 6; // Min DAC value (0)
        delay(1);       // Half-period of the square wave
    }
}
