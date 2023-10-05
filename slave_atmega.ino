#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define ATMEGA_SLAVE 0x50


uint8_t write_data,recv_data;
uint8_t address=0x50;
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


void TWI_init_slave() {

    TWAR = ATMEGA_SLAVE<< 1; // Endereço do escravo I2C

    TWCR = (1 << TWEN);
    TWCR |= (1 << TWEA);
}

uint8_t TWI_read_slave() {
  TWCR= (1<<TWINT)|(1<<TWEA)|(1<<TWEN);    // Wait for TWINT flag
  while((TWSR & 0xF8)!=0x80);        // Wait for acknowledgement
  recv_data=TWDR; // Get value from TWDR
    return recv_data;
}
void TWI_match_read_slave(void) //Function to match the slave address and slave dirction bit(read)
{
  //Serial.println(0);
    while((TWSR & 0xF8)!= 0x60)  // Loop till correct acknoledgement have been received
    {
        // Get acknowlegement, Enable TWI, Clear TWI interrupt flag
        TWCR=(1<<TWEA)|(1<<TWEN)|(1<<TWINT);    
        while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag
    }
} 

void setup() {
  TWI_init_slave();
  USART_Init(103);

}

void loop() {

  TWI_match_read_slave();
  
  recv_data=TWI_read_slave();
  recv_data=64;
  uint8_t dec=recv_data/10;
  uint8_t unid=recv_data%10;

  USART_Transmit(dec+48);
   USART_Transmit(unid+48); 
  USART_Transmit(10);    
}
