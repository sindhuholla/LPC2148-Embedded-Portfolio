/*
This program will turn on the DC motor on the push button
press and turns off the DC motor on the next press.
*/

/**********************************************

Submission Details:
Name: Sindhu Holla
Problem Statement: DC Motor Interfacing with LPC2148

Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
P0.0, P0.1 -> DC Motor
P0.3 -> Push Button

************************************************/

#include <lpc214x.h>
#include "Timer.h"
#include "PLL.h"

#define bit(x) (1 << (x))

// Motor pins
#define MOTOR_IN1 bit(0)  // P0.0
#define MOTOR_IN2 bit(1)  // P0.1
#define MOTOR_EN  bit(2)  // Optional enable pin, if needed

#define BUTTON_PIN bit(3) // P0.3

int main() {
	
    unsigned int motorState = 1;  // 0 = OFF, 1 = ON
    unsigned int buttonPressed = 0; // 0 = Not pressed, 1 = Pressed
		
		// Timer Initialisation
		PLL_init(PLL0,PLL0_60MHz_pclk_60MHz_cclk);
		Timer0_init_1sec(DELAY_1MS);
		
    // Configure GPIO pins
    IO0DIR = MOTOR_IN1 | MOTOR_IN2 | MOTOR_EN;  // Set P0.0, P0.1, and P0.2 as outputs
    IO0CLR = MOTOR_IN1 | MOTOR_IN2;  // Ensure motor is OFF initially
    IO0SET = MOTOR_EN;  // Enable the motor driver if needed

    // Configure button pin as input
    IO0DIR &= ~BUTTON_PIN;  // Set P0.3 as input
    IO0SET = BUTTON_PIN;    // Enable internal pull-up resistor on P0.3

    while (1) {
        // Check button state
        if (!(IO0PIN & BUTTON_PIN)) { // Button pressed (active low)
            if (!buttonPressed) {  // Detect button press
                // Toggle motor state
                if (motorState) {
                    IO0CLR = MOTOR_IN1 | MOTOR_IN2; // Turn off motor
                    motorState = 0;
                } else {
                    IO0SET = MOTOR_IN1; // Forward direction
                    IO0CLR = MOTOR_IN2;
                    motorState = 1;
                }
                buttonPressed = 1; // Set button pressed flag
            }
        } else {
            buttonPressed = 0; // Reset button pressed flag
        }

        delay(60); // Simple delay for debouncing
    }
}
