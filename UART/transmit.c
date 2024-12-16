/*
This program transmits data ('1') to a second LPC2148 microcontroller via UART 
when the push button interfaced to this LPC2148 is pressed. 
The button press is detected using active-low logic.
*/

/****************************************************

Submission Details:
Name: Sindhu Holla
File: UART Communication between Two LPC2148

Clock Settings:
	FOSC	>>	12MHz (onboard oscillator frequency)
	PLL		>>	M=5, P=2 (Phase Locked Loop settings)
	CCLK	>>	60MHz (CPU clock frequency)
	PCLK	>>	15MHz (Peripheral clock frequency)
		
Hardware Setup:
	P0.10 -> Push Button (active-low)
	P0.0  -> TX (UART0 Transmit)
	P0.1  -> RX (UART0 Receive)

*****************************************************/

#include <lpc214x.h>  // Include the LPC214x microcontroller header file

// Function to initialize UART0 for communication
void uart_init(void) {
    PINSEL0 |= 0x00000005;  // Configure P0.0 as TXD0 and P0.1 as RXD0 (UART0 pins)
    U0LCR = 0x83;           // Configure UART0: 8-bit data, 1 stop bit, no parity, DLAB = 1
    U0DLM = 0x00;           // Set high byte of baud rate divisor to 0
    U0DLL = 97;             // Set low byte of baud rate divisor for a baud rate of 9600
    U0LCR = 0x03;           // Disable DLAB (lock baud rate configuration)
}

// Function to transmit a character via UART0
void uart_transmit(char data) {
    while (!(U0LSR & 0x20)); // Wait until the transmitter holding register (THR) is empty
    U0THR = data;            // Load the data into THR to transmit
}

// Function to initialize GPIO for push button
void gpio_init(void) {
    IO0DIR &= ~(1 << 10);    // Configure P0.10 as input (push button pin)
}

// Main program
int main(void) {
    uart_init();  // Initialize UART0 for communication
    gpio_init();  // Initialize GPIO for push button input

    while (1) {
        if (!(IO0PIN & (1 << 10))) {        // Check if push button is pressed (active-low logic)
            uart_transmit('1');             // Transmit the character '1' via UART0
            while (!(IO0PIN & (1 << 10)));  // Debounce: Wait until the button is released
        }
    }
}
