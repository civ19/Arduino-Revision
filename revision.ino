#include <avr/io.h>        // Contains the actual memory addresses of the silicon registers
#include <avr/interrupt.h> // Contains the low-level interrupt macros (ISR, sei, cli)

// The absolute entry point of the microprocessor execution pipeline
int main(void) {
    // Set Data Direction Register for Port B, Bit 5 (Digital Pin 13 on Arduino Uno) to OUTPUT
    // This is the bare-metal equivalent of pinMode(13, OUTPUT)
    DDRB |= (1 << DDB5);

    // Disable all global interrupts during hardware configuration
    cli();          

    // Reset Control Registers to a clean state
    TCCR1A = 0;     
    TCCR1B = 0;     
    TCNT1  = 0;     // Clear the counter bucket register

    // Set the target finish line value
    OCR1A = 1999;   

    // Turn on CTC (Clear Timer on Compare) Mode
    TCCR1B |= (1 << WGM12);  

    // Set the Prescaler to 8
    TCCR1B |= (1 << CS11);   

    // Enable the Timer 1 Compare Match A Interrupt
    TIMSK1 |= (1 << OCIE1A); 

    // Re-enable global interrupts
    sei();          

    // The infinite execution loop (The bare-metal equivalent of void loop())
    while (1) {
        // CPU spins here doing absolutely nothing.
        // The hardware timer handles everything in the background.
    }

    return 0; // Standard C compliance, though the CPU will never actually reach here
}

// The Interrupt Service Routine (ISR)
ISR(TIMER1_COMPA_vect) {
    // Toggle Port B, Bit 5 (Pin 13) by writing a 1 to its input register PINB
    // This is the fastest, lowest-level way to flip an output pin in hardware
    PINB |= (1 << PINB5); 
}