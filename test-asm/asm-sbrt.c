// asm-sbrt on atmega32

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

void toggleBRoutine();

ISR (INT0_vect){
	toggleBRoutine();
}

int main(void){
	// Setup code
	DDRB = 0xFF; // Setting PORTB as output
	DDRD = 0XFF; // Provides some strange protection against false interrputs
	GICR = 0xC0; // Enabling interrupts
	MCUCR |= 11<<ISC00; //Setting up INT0 as rising edge
	sei(); // Enabling interrupt flag
	while(1){
		_delay_ms(1000);
	}
}
