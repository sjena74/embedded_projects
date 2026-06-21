// bare-metal-timer-interrupt

// configure internal clock prescale, when internal count == external count, isr interrupt 

#include <stdint.h> // allows for defining points of register size
#include <avr/interrupt.h> // allows for ISR


#define TCCR1B *((volatile uint8_t*)0x81)
#define TIMSK1 *((volatile uint8_t*)0x6F)
#define DDRB *((volatile uint8_t*)0x24)
#define PORTB *((volatile uint8_t*)0x25)
#define OCR1A *((volatile uint16_t*)0x88)

ISR(TIMER1_COMPA_vect) {
  PORTB ^= (1 << 5);
}




int main(void) {

  DDRB |= (1 << 5);

  TCCR1B = 0b1101; // set WGM12 for CTC mode, CS12/CS10 for 1024x prescale for timer
  // (16,000,000 / 1024 / 2) - 1 = 7811 for 1 blink per .5 second
  OCR1A = 7811; // can't configure 16,000,000 to 16-bit register so must use prescale.

  TIMSK1 |= 0b10; // to match OCR1A compare register
  sei(); // now start global interrupt after setup

  while (1) {


  }
  return 0;

}