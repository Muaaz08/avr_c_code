#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (((FOSC / (BAUD * 16UL))) - 1)

void USART_Init(unsigned int ubrr) {
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  /*Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)));
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void print_String(char* str) {
  unsigned char j = 0;
  while (str[j] != 0) {
    USART_Transmit(str[j]);
    j++;
  }
}

int main(void) {

  USART_Init(MYUBRR);
  while (1) {
    print_String("Hello World\n");
    _delay_ms(100);
  }
}
