#include <stdint.h>

#define DDRB *((volatile uint8_t*)0x24)
#define PORTB *((volatile uint8_t*)0x25)
#define UBRR0L *((volatile uint8_t*)0xC4)
#define UCSR0B *((volatile uint8_t*)0xC1)
#define UCSR0C *((volatile uint8_t*)0XC2)
#define UCSR0A *((volatile uint8_t*)0xC0)
#define UDR0 *((volatile uint8_t*)0xC6)
void uart_init(void) {
  UBRR0L = 103; // (16,000,000 / 16 / 9600) 9600 is baud rate
  UCSR0B |= (1 << 3) | (1 << 4); // for tx/rx enable
  UCSR0C |= (1 << 1) | (1 << 2); // frame format of 8 data bits, no parity bit, 1 stop bit

}

void uart_transmit(uint8_t data) {
  while (!(UCSR0A & (1 << 5))) { // check to see if bit 5 is on

  }
  UDR0 = data;

}

uint8_t uart_recieve(void) {
  while (!(UCSR0A & (1 << 7))) { // check to see if bit 7 is on

  }
  return UDR0;

}

int main(void) {

  uart_init();
  DDRB |= (1 << 5); // configure PORTB, bit 5

  while (1) {

    uint8_t command = uart_recieve();

    if (command == '0') {
      PORTB &= ~(1 << 5);
      uart_transmit('O');
      uart_transmit('F');
      uart_transmit('F');
      uart_transmit('\n');
    }
    if (command == '1') {
      PORTB |= (1 << 5);
      uart_transmit('O');
      uart_transmit('N');
      uart_transmit('\n');

    }

  }

}