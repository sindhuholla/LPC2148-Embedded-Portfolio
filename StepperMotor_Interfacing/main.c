/*
This program turns stepper motor clockwise, anticlockwise & turns off based on
push buttons
1st Push Button -> Clockwise
2nd Push Button -> Anti-Clockwise
3rd Push Button -> Stop
*/
/************************************************

Submission Details:
Name: Sindhu Holla
Problem Statement: Stepper motor interfacing with LPC2148

Clock Settings:
	FOSC : 12MHZ
	PLL  : M=5, P=2
	CCLK : 60MHZ
	PCLK : 12MHZ

Hardware Setup:
LEDs -> P0.4, P0.5, P0.6, P0.7
Push Button -> P0.0, P0.1, P0.2

********************************************/



#include <LPC214X.H>
#include "Timer.h"
#include "PLL.h"

// Define stepper motor control patterns
#define CW_STEP1 0x30 // 0011 0000
#define CW_STEP2 0x60 // 0110 0000
#define CW_STEP3 0xC0 // 1100 0000
#define CW_STEP4 0x90 // 1001 0000

#define CCW_STEP1 0x90 // 1001 0000
#define CCW_STEP2 0xC0 // 1100 0000
#define CCW_STEP3 0x60 // 0110 0000
#define CCW_STEP4 0x30 // 0011 0000

// Define step sequences in arrays
const unsigned int CW_STEPS[] = { CW_STEP1, CW_STEP2, CW_STEP3, CW_STEP4 };
const unsigned int CCW_STEPS[] = { CCW_STEP1, CCW_STEP2, CCW_STEP3, CCW_STEP4 };

// Define pushbutton pins (example pins, adjust as necessary)
#define BUTTON1_PIN (1 << 0) // P0.0
#define BUTTON2_PIN (1 << 1) // P0.1
#define BUTTON3_PIN (1 << 2) // P0.2

void step_motor(const unsigned int *steps, unsigned int num_steps);
int read_buttons(void);

int main(void)
{
    // Initialize variables
    const unsigned int *steps = 0; // Use 0 instead of NULL for pointer initialization
    unsigned int num_steps = 0;
    int prev_buttons = 0;
    int motor_running = 0;
    unsigned int step_index = 0;
		
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
	
    // Configure GPIO pins
    PINSEL0 = 0x00; // Set all pins as GPIO
    IODIR0 = (0xF << 4); // Set P0.4 - P0.7 as outputs for stepper motor
    IODIR0 &= ~(BUTTON1_PIN | BUTTON2_PIN | BUTTON3_PIN); // Set P0.0, P0.1, and P0.2 as inputs

    while (1)
    {
        int buttons = read_buttons();

        if (buttons & BUTTON1_PIN)
        {
            // Button 1 pressed: Rotate clockwise
            if (prev_buttons != BUTTON1_PIN)
            {
                steps = CW_STEPS;
                num_steps = 4;
                motor_running = 1;
                prev_buttons = BUTTON1_PIN;
            }
        }
        else if (buttons & BUTTON2_PIN)
        {
            // Button 2 pressed: Rotate counterclockwise
            if (prev_buttons != BUTTON2_PIN)
            {
                steps = CCW_STEPS;
                num_steps = 4;
                motor_running = 1;
                prev_buttons = BUTTON2_PIN;
            }
        }
        else if (buttons & BUTTON3_PIN)
        {
            // Button 3 pressed: Stop the motor
            if (prev_buttons != BUTTON3_PIN)
            {
                motor_running = 0;
                prev_buttons = BUTTON3_PIN;
            }
        }
        else
        {
            if (motor_running)
            {
                // Continue running the motor if it was running
                step_motor(steps, num_steps);
            }
            else
            {
                // Optionally stop the motor or hold its last position
                IOCLR0 = 0xF0; // Ensure all motor pins are cleared
            }
        }
    }
}

void step_motor(const unsigned int *steps, unsigned int num_steps)
{
    static unsigned int i = 0;

    if (steps != 0 && num_steps > 0) // Use 0 instead of NULL for pointer check
    {
        IOCLR0 = 0xF0; // Clear P0.4 - P0.7
        IOSET0 = steps[i]; // Set the motor to the current step
        delay(100); // Delay to allow the motor to move
        i = (i + 1) % num_steps; // Move to the next step in the sequence
    }
}

int read_buttons(void)
{
    // Read the state of the pushbuttons
    return (IOPIN0 & (BUTTON1_PIN | BUTTON2_PIN | BUTTON3_PIN));
}
