/*
Author 		  :  Sindhu Holla
Roll no.    :  241039004
Board 		  :  arm 7
Processor 	:  LPC2148
Experiment  :  3 LED Blinking in sequence

		
Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
	

*/

#include <lpc214x.h>  // Include header file for LPC214x microcontroller

// Initialize Timer 0 for delay
void init_timer0(void) {
    T0CTCR = 0X00;          // Configure Timer 0 as a timer
    T0PR = 59999;           // Load Prescaler value to achieve 1 millisecond (PCLK = 60MHz / 60,000)
    T0TCR = 0X02;           // Reset the timer
}

// Function to create a delay using Timer 0 (in milliseconds)
void timer_delay_ms(unsigned int ms) {
    T0TCR = 0X02;           // Reset the timer
    T0TCR = 0x01;           // Enable the timer
    while (T0TC < ms);      // Wait for the desired delay (in milliseconds)
    T0TCR = 0X02;           // Reset the timer
    T0TCR = 0x00;           // Stop the timer
    T0TC = 0x00;            // Clear the timer counter
}

// Main function
int main()
{
    init_timer0();          // Initialize the timer

    PINSEL0 = 0x0000;       // Configure all P0 pins as GPIO (General Purpose Input/Output)
    IODIR0 = 0x07;          // Set P0.0, P0.1, and P0.2 as output pins (0x07 = 0000 0111 in binary)

    while (1)               // Infinite loop
    {
        IOSET0 = 0x01;      // Set P0.0 high (turn LED connected to P0.0 ON)
        timer_delay_ms(100); // Timer delay of 100 milliseconds

        IOSET0 = 0x02;      // Set P0.1 high (turn LED connected to P0.1 ON)
        timer_delay_ms(100); // Timer delay of 100 milliseconds

        IOSET0 = 0x04;      // Set P0.2 high (turn LED connected to P0.2 ON)
        timer_delay_ms(100); // Timer delay of 100 milliseconds

        IOCLR0 = 0x04;      // Clear P0.2 (turn LED connected to P0.2 OFF)
        timer_delay_ms(100); // Timer delay of 100 milliseconds

        IOCLR0 = 0x02;      // Clear P0.1 (turn LED connected to P0.1 OFF)
        timer_delay_ms(100); // Timer delay of 100 milliseconds

        IOCLR0 = 0x01;      // Clear P0.0 (turn LED connected to P0.0 OFF)
        timer_delay_ms(100); // Timer delay of 100 milliseconds
    }
}
