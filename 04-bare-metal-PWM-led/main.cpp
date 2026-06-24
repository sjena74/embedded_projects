#include <stdint.h>

#define DDRB *((volatile uint8_t*)0x24)
#define TCCR1A *((volatile uint8_t*)0x80)
#define TCCR1B *((volatile uint8_t*)0x81)
#define OCR1A *((volatile uint16_t*)0x88)

void delay(volatile uint32_t delay) {
  while (delay--); // burning CPU cycles for delay
}

int main(void) {
  DDRB |= (1 << 1); // Pin 9 on arduino uno
  
  TCCR1A |= (1 << 7); // clear OC1A on match
  TCCR1A |= (1 << 0); // 8-bit fast PWM mode
  TCCR1B |= (1 << 3); // 8-bit fast PWM mode
  TCCR1B |= (1 << 1); // prescale x8

  


  while(1)  {
    for (int i = 0; i <= 255; i++) { // light-up
    OCR1A = i;
    delay(5000);
  }

  for (int i = 255; i >= 0; i--) { // fade
    OCR1A = i;
    delay(5000);
  }
  }
} 