/*
Author 		: Sindhu Holla
Roll no.  : 241039004
Board 		: LPC2148
Experiment: Displaying Scrolling Text on LCD

		
Clock Settings:
	FOSC	>>	12MHz (onboard)
	PLL		>>	M=5, P=2
	CCLK	>>  60MHz
	PCLK	>>  15MHz 
		
Hardware Setup:-
	LCD data pin :-P0.16-P0.23 
	RS-P0.4
	RW-P0.5
	EN-P0.6
problem statement : LCD interfacing (Scrolling the message) */



#include <lpc214x.h>  // Include the LPC214x microcontroller specific header file
#include <stdint.h>   // Include the standard integer types header

// Define bit masks for controlling the LCD
#define EN_PIN 0x00000040  // Enable pin bit mask
#define RS_PIN 0x00000010  // Register Select pin bit mask
#define RW_PIN 0x00000020  // Read/Write pin bit mask
#define DATA_MASK 0xFFFF00FF  // Data mask to isolate data bits
#define LCD_WIDTH 16  // Width of the LCD, adjust if a different size LCD is used

// Declare external delay function and initialization from timer_delay.c
extern void timer_delay_ms(uint16_t ms);
extern void init_timer0(void);

// Function to write a command or data to the LCD
void LCD_WRITE(unsigned int data, unsigned int is_command) {
    if (is_command) {
        IO0CLR = RS_PIN; // Set RS pin to 0 for command mode
    } else {
        IO0SET = RS_PIN; // Set RS pin to 1 for data mode
    }
    IO0PIN = ((IO0PIN & DATA_MASK) | (data << 8)); // Write data to LCD (shifted to the correct position)
    IO0SET = EN_PIN; // Set EN pin to 1 to latch data
    timer_delay_ms(2); // Delay to ensure data is latched
    IO0CLR = EN_PIN; // Set EN pin to 0 to complete the write operation
    timer_delay_ms(5); // Additional delay to ensure data is processed
}

// Function to initialize the LCD
void LCD_INIT(void) {
    IO0DIR = 0x0000FFF0; // Set direction for data and control lines (output mode)
    timer_delay_ms(20); // Initial delay to ensure LCD is ready
    LCD_WRITE(0x38, 1);  // Send initialization command (function set: 8-bit interface, 2 lines, 5x7 font)
    LCD_WRITE(0x0C, 1);  // Display on, cursor off
    LCD_WRITE(0x06, 1);  // Auto increment cursor position
    LCD_WRITE(0x01, 1);  // Clear display
    LCD_WRITE(0x80, 1);  // Set cursor to the first line, first position
}

// Function to send a command to the LCD
void LCD_CMD(unsigned int cmd) {
    LCD_WRITE(cmd, 1); // Send command
}

// Function to send a single character to the LCD
void LCD_CHAR(unsigned int ch) {
    LCD_WRITE(ch, 0); // Send data (character)
}

// Function to send a string of characters to the LCD
void LCD_STRING(const char* msg) {
    while (*msg) {
        LCD_CHAR(*msg++); // Send each character of the string
    }
}

// Function to scroll a message across the LCD display
void LCD_SCROLL(const char* msg, unsigned int delay) {
    unsigned int len = 0;
    const char* start = msg;
    unsigned int i;
    unsigned int pos;
    
    // Find the length of the message
    while (msg[len]) len++;
    
    // Scroll the message across the display
    for (pos = 0; pos <= len + LCD_WIDTH; pos++) {
        LCD_CMD(0x01); // Clear display
        LCD_CMD(0x80); // Move cursor to the beginning of the first line

        // Display the substring of the message
        for (i = pos; i < pos + LCD_WIDTH && i < len; i++) {
            LCD_CHAR(start[i]); // Send each character within the current display window
        }

        timer_delay_ms(delay); // Delay between each scroll step
    }
}

// Main function
int main(void) {
    init_timer0(); // Initialize Timer 0 for delays
    LCD_INIT(); // Initialize the LCD
    LCD_SCROLL("Hello, Welcome to MSIS manipal.", 300); // Scroll a message across the LCD with a delay
    return 0; // Return from main
}

