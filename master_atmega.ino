#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>

#define ATMEGA_SLAVE 0x50

void TWI_init_master() {
    // Configurar a inicialização do barramento I2C
    TWSR=0b00000001;
    TWBR = 18; // Defina o bitrate do barramento I2C para 100 kHz
    TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
}

void TWI_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
}

void TWI_stop() {
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
    while (TWCR & (1 << TWSTO));
}

void TWI_write_data(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
}

void setup() {
  TWI_init_master();
}

void loop() {
  TWI_start();
  TWI_write_data(ATMEGA_SLAVE << 1);
  TWI_write_data(0x40);
  TWI_stop();
  _delay_ms(500);  
}
