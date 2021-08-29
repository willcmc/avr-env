# Welcome to my AVR sandbox!
This is a repo for AVR testing and development, and serves as a compendium of my work.

### test-asm
- Mixing C and ASM
- Switch on PORTD toggles PORTB via an interrupt which calls an assembly subroutine to do the toggling.
- Written for `avr-gcc` and might need modification before it can be used on AS7 or `avra`.
