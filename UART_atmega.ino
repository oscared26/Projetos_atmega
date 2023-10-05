#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
//#include <util/setbaud.h>

//#define F_CPU 16000000UL // Frequência do ATmega328P




void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
  UCSR0B = 0b00011100;
	//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	//UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0C = 0b00011100;
}

void USART_Transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

/*
ISR(USART_RX_vect) {
    // Esta função é chamada quando um caractere é recebido

    uint8_t receivedData = UDR0; // Ler o caractere recebido

    // Faça algo com os dados recebidos aqui, como processá-los ou armazená-los
}
*/

void setup() 
{
	USART_Init(103);
    // Habilitar interrupções globais
    //sei();
}

void loop() {

delay(5);
USART_Transmit(55);
delay(5);
//USART_Transmit(50);
//USART_Transmit(52);
//USART_Transmit(10);

}
