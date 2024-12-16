#include <lpc214x.h>
#include <stdint.h>  // Include standard integer types

// Initialize Timer 0 for delays
void init_timer0(void) {
    T0CTCR = 0x00;          // Configure Timer 0 as a timer (count mode)
    T0PR = 59999;           // Prescaler value to achieve 1 millisecond delay (assuming PCLK = 60 MHz)
    T0TCR = 0x02;           // Reset Timer 0
}

// Timer delay function for a specified number of milliseconds
void timer_delay_ms(uint16_t ms) {
    T0TCR = 0x02;           // Reset Timer 0
    T0TCR = 0x01;           // Start Timer 0
    while (T0TC < ms);      // Wait until the timer counter reaches the desired delay
    T0TCR = 0x00;           // Stop Timer 0
    T0TC = 0x00;            // Reset Timer 0 counter to 0
}
