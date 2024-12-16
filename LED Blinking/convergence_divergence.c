#include <lpc214x.h>  // Include header file for LPC214x microcontroller

// Initialize Timer 0 for delay
void init_timer0(void) {
    T0CTCR = 0x00;          // Configure Timer 0 as a timer (count mode)
    T0PR = 59999;           // Prescaler value to achieve 1 millisecond (assuming PCLK = 60 MHz)
    T0TCR = 0x02;           // Reset Timer 0
}

// Function to create a delay using Timer 0 (in milliseconds)
void timer_delay_ms(unsigned int ms) {
    T0TCR = 0x02;           // Reset Timer 0
    T0TCR = 0x01;           // Start Timer 0
    while (T0TC < ms);      // Wait until the timer counter reaches the desired delay
    T0TCR = 0x00;           // Stop Timer 0
    T0TC = 0x00;            // Reset Timer 0 counter to 0
}

int main() {
    // Initialize Timer 0
    init_timer0();

    // Configure GPIO pins
    PINSEL0 = 0x00000000;  // Set all P0 pins as GPIO (General Purpose Input/Output)
    PINSEL2 = 0x00000000;  // Set all P1 pins as GPIO (General Purpose Input/Output)
    
    // Set direction for Port 0 and Port 1 pins
    IODIR0 = 0x0F;         // Set P0.0 - P0.3 as output pins (binary 0000 1111)
    IODIR1 = (0x0F) << 16; // Set P1.16 - P1.19 as output pins (0x0F shifted left by 16 bits)

    while (1) {  // Infinite loop
        // Convergence pattern (outer LEDs to inner LEDs)
        IOSET0 = 0x01;          // Set P0.0 high (turn LED connected to P0.0 ON)
        IOSET1 = 0x08 << 16;    // Set P1.19 high (turn LED connected to P1.19 ON)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOSET0 = 0x02;          // Set P0.1 high (turn LED connected to P0.1 ON)
        IOSET1 = 0x04 << 16;    // Set P1.18 high (turn LED connected to P1.18 ON)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOSET0 = 0x04;          // Set P0.2 high (turn LED connected to P0.2 ON)
        IOSET1 = 0x02 << 16;    // Set P1.17 high (turn LED connected to P1.17 ON)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOSET0 = 0x08;          // Set P0.3 high (turn LED connected to P0.3 ON, center LED)
        IOSET1 = 0x01 << 16;    // Set P1.16 high (turn LED connected to P1.16 ON, center LED)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        // Divergence pattern (inner LEDs to outer LEDs)
        IOCLR0 = 0x08;          // Clear P0.3 (turn off LED connected to P0.3)
        IOCLR1 = 0x01 << 16;    // Clear P1.16 (turn off LED connected to P1.16)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOCLR0 = 0x04;          // Clear P0.2 (turn off LED connected to P0.2)
        IOCLR1 = 0x02 << 16;    // Clear P1.17 (turn off LED connected to P1.17)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOCLR0 = 0x02;          // Clear P0.1 (turn off LED connected to P0.1)
        IOCLR1 = 0x04 << 16;    // Clear P1.18 (turn off LED connected to P1.18)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
        
        IOCLR0 = 0x01;          // Clear P0.0 (turn off LED connected to P0.0)
        IOCLR1 = 0x08 << 16;    // Clear P1.19 (turn off LED connected to P1.19)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds

        // Clear all LEDs before repeating the pattern
        IOCLR0 = 0x0F;          // Clear P0.0 - P0.3 (turn off LEDs connected to P0.0 - P0.3)
        IOCLR1 = (0x0F) << 16;  // Clear P1.16 - P1.19 (turn off LEDs connected to P1.16 - P1.19)
        timer_delay_ms(50);     // Timer delay of 50 milliseconds
    }
}
