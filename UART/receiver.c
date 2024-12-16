/*
This program receives data from another LPC2148 microcontroller via UART. 
When the received data indicates that a push button interfaced to the other LPC2148 is pressed, 
it switches on the LED connected to this LPC2148 for a short duration.
*/

/****************************************************

Submission Details:
Name: Sindhu Holla
File: UART Communication between Two LPC2148s

Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:
	P0.8 -> LED
	P0.0 -> TX (UART0 Transmit)
	P0.1 -> RX (UART0 Receive)

*****************************************************/

#include <lpc214x.h>  // Include header file for LPC214x microcontroller

// Function to initialize UART0 for communication
void uart_init(void) {
    PINSEL0 |= 0x00000005;  // Configure P0.0 as TXD0 and P0.1 as RXD0 (UART0)
    U0LCR = 0x83;           // Set UART0 to 8-bit data, 1 stop bit, no parity, and enable DLAB
    U0DLM = 0x00;           // Set high byte of baud rate divisor to 0
    U0DLL = 97;             // Set low byte of baud rate divisor for a baud rate of 9600
    U0LCR = 0x03;           // Disable DLAB (lock baud rate configuration)
}

// Function to receive a character via UART0
char uart_receive(void) {
    while (!(U0LSR & 0x01)); // Wait until UART0 receiver buffer (RBR) has data available
    return U0RBR;            // Return the received character from the RBR
}

// Function to initialize GPIO for LED control
void gpio_init(void) {
    IO0DIR |= (1 << 8);      // Configure P0.8 as an output pin (for the LED)
}

// Function to create a simple delay
void delay(int time) {
    int i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 6000; j++);  // Inner loop creates a delay
    }
}

// Main program
int main(void) {
    uart_init();   // Initialize UART0 for communication
    gpio_init();   // Initialize GPIO for LED control
		
    while (1) {
        char received_data = uart_receive();  // Wait for data to be received via UART0

        if (received_data == '1') {          // If the received data is '1'
            IO0SET = (1 << 8);               // Turn on the LED (set P0.8 high)
            delay(500);                      // Wait for a short delay
            IO0CLR = (1 << 8);               // Turn off the LED (clear P0.8)
        }
    }
}
