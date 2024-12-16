/*
This program generates Triangle Wave
*/
/****************************************************

Submission Details:
Name: Sindhu Holla
File: Triangle wave generator

Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
P0.25 -> Oscilloscope (A)

*****************************************************/

#include "header.h"
#include "Timer.h"
#include "PLL.h"

int main() {
    // Declare variables at the beginning of the block
    int value = 0;
    int step = 1; // Increment or decrement step size

    // Initialize DAC
    initDAC();
	
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
    
    while (1) {
        // Write the current value to DAC (shift left to match DACR format)
        DACR = value << 6;

        // Generate rising and falling edge
        value += step;

        // If the value reaches the upper or lower bound, reverse the direction
        if (value >= 1023) {
            step = -1; // Start decreasing
        } else if (value <= 0) {
            step = 1;  // Start increasing
        }

        // Control the speed of the wave (adjust the delay for desired frequency)
        delay(1);
    }
}
