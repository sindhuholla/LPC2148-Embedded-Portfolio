/*
Author 		:  Sindhu Holla
Roll no.  :  241039004
Board 		:  LPC2148
Experiment:  Problem statement-Displaying Text on LCD,one character at a time
		
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
 
*/

#include <lpc214x.h>  // Include header for LPC214x microcontroller
#include <stdint.h>   // Include header for standard integer types
#include <stdlib.h>   // Include standard library functions
#include <stdio.h>    // Include standard input/output functions

// Declare external delay function from the timer_delay.c file
extern void timer_delay_ms(uint16_t ms);
extern void init_timer0(void);

// Function to send a command to the LCD
void LCD_CMD(char command)
{
    IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (command << 8) );  // Set command bits in the data register
    IO0SET = 0x00000040; /* Set EN (Enable) pin to 1 */
    IO0CLR = 0x00000030; /* Clear RS (Register Select) and RW (Read/Write) pins (RS = 0, RW = 0) */
    timer_delay_ms(2);  // Wait for command to be processed
    IO0CLR = 0x00000040; /* Clear EN pin (EN = 0), RS and RW remain unchanged (RS = 0, RW = 0) */
    timer_delay_ms(5);  // Wait for LCD to execute the command
}

// Function to initialize the LCD
void LCD_INIT(void)
{
    IO0DIR = 0x0000FFF0; /* Set P0.8 to P0.15 as data output pins for LCD, P0.4, P0.5, P0.6 as RS, RW, and EN pins */
    timer_delay_ms(20);  // Initial delay to ensure LCD is ready
    LCD_CMD(0x38);  /* Send initialization command (function set: 8-bit interface, 2 lines, 5x7 font) */
    LCD_CMD(0x0C);  /* Display on, cursor off */
    LCD_CMD(0x06);  /* Auto increment cursor position */
    LCD_CMD(0x01);  /* Clear display */
    LCD_CMD(0x80);  /* Set cursor to first line, first position */
}

// Function to send a string to the LCD
void LCD_STRING(char* msg)
{
    uint8_t i = 0;
    while(msg[i] != 0)  // Loop through each character in the string
    {
        IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg[i] << 8) );  // Set character data bits in the data register
        IO0SET = 0x00000050; /* Set RS (Register Select) and EN (Enable) pins to 1 (RS = 1, EN = 1) */
        IO0CLR = 0x00000020; /* Clear RW (Read/Write) pin (RW = 0) */
        timer_delay_ms(2);  // Wait for character to be written to the LCD
        IO0CLR = 0x00000040; /* Clear EN pin (EN = 0), RS and RW remain unchanged (RS = 1, RW = 0) */
        timer_delay_ms(5);  // Wait for LCD to process the character
        i++;  // Move to the next character in the string
    }
}

// Function to send a single character to the LCD
void LCD_CHAR(char msg)
{
    IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg << 8) );  // Set character data bits in the data register
    IO0SET = 0x00000050; /* Set RS (Register Select) and EN (Enable) pins to 1 (RS = 1, EN = 1) */
    IO0CLR = 0x00000020; /* Clear RW (Read/Write) pin (RW = 0) */
    timer_delay_ms(2);  // Wait for character to be written to the LCD
    IO0CLR = 0x00000040; /* Clear EN pin (EN = 0), RS and RW remain unchanged (RS = 1, RW = 0) */
    timer_delay_ms(5);  // Wait for LCD to process the character
}

// Main function
int main(void)
{
    uint8_t j;
    j = 0;  // Initialize variable (not used further)
    
    // Initialize Timer 0
    init_timer0();
    
    // Initialize the LCD
    LCD_INIT();  
    
    // Display "Hello" on the first line of the LCD
    LCD_STRING("Hello");  
    
    // Move cursor to the second line
    LCD_CMD(0xC0);  
    
    // Display "Welcome to MSIS" on the second line of the LCD
    LCD_STRING("Welcome to MSIS");  
    
    return 0;  // Return from main function
}

