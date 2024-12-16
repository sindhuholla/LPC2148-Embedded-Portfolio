/*
This program generates Ramp Wave
*/
/****************************************************

Submission Details:
Name: Sindhu Holla
File: DAC-Ramp wave generation

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
    // Declare variables at the beginning
    int value = 0;  // DAC output value

    // Initialize DAC
    initDAC();
		
		// Timer Initialisation
		PLL_init(PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1Ms(DELAY_1MS);
    
    while (1) {
        // Write the current value to DAC (shift left to match DACR format)
        DACR = value << 6;

        // Increment the DAC value for ramp up
        value++;

        // If the value reaches the max (1023), reset to 0 for ramp waveform
        if (value > 1023) {
            value = 0;
        }

        // Control the slope (adjust the delay for desired ramp speed)
        delay(20);
    }
}
