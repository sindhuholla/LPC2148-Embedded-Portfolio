/*
This program generates Sine Wave
*/
/****************************************************

Submission Details:
Name: Sindhu Holla
File: Sine Wave Generator

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
#include <math.h>     // Required for sine function

#define PI 3.14159265
#define SINE_STEPS 100  // Number of steps for one complete sine wave

// Lookup table to store pre-calculated sine values
unsigned int sine_wave[SINE_STEPS];

void generate_sine_wave_table(void);

int main() {
		// Declare variables
    int index = 0;

    // Initialize DAC
    initDAC();
	
	// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);

    // Generate the sine wave lookup table
    generate_sine_wave_table();
    
    while (1) {
        // Output the current sine wave value from the lookup table
        DACR = sine_wave[index] << 6;

        // Move to the next point in the sine wave
        index++;

        // If the index reaches the end of the table, reset to 0
        if (index >= SINE_STEPS) {
            index = 0;
        }

        // Delay to control the frequency of the sine wave
        delay(1);
    }
}

void generate_sine_wave_table(void) {
    int i;
    for (i = 0; i < SINE_STEPS; i++) {
        // Calculate the sine value for the current step, scaled to fit DAC range (0-1023)
        float angle = (2 * PI * i) / SINE_STEPS;   // Angle in radians
        sine_wave[i] = (unsigned int)((sin(angle) + 1.0) * 511.5);  // Scale sine to 0-1023
    }
}
