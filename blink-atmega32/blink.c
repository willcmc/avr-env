// Atmega32 Blink

#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz
#endif

#include<avr/io.h>
#include<util/delay.h>

int main(void){
	DDRB |= 0b11;
	
	while(1){
		PORTB |= 0b1;
		_delay_ms(100);
		PORTB &= 0b0;
		_delay_ms(400);
		PORTB |= 0b10;
		_delay_ms(100);
		PORTB &= 0b0;
		_delay_ms(100);
		PORTB |= 0b10;
		_delay_ms(100);
		PORTB &= 0b0;
		_delay_ms(400);
	}

}
