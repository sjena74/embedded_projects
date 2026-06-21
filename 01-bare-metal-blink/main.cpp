#include <stdint.h>

#define LEDPORTB *((volatile uint8_t*)0x25)
#define DDRB *((volatile uint8_t*)0x24)

void delay(volatile uint32_t count) {
  while(count) {
    count--;
  }
}



int main(void) {
  DDRB |= (1 << 5);
  while (1) {
    LEDPORTB |= (1 << 5);
    delay(2000000);
    LEDPORTB &= ~(1 << 5);
    delay(2000000);
  
  }


}