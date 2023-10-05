#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <compat/twi.h>

#define PCA9685_ADDRESS 0x40
#define PRESCALE_VALUE 0x03

uint8_t slaveAddress = 0x50;
uint8_t sendData = 0xAA;
unsigned char write_data=0x01, recv_data;
unsigned char address=0x20, read=1, write=0;


void TWI_init_master() 
{  
  //TWSR=0b00000011;    
  //TWBR=0x48;    
  //TWCR = (1 << TWEN);

  TWSR=0b00000001;
  TWBR=18;
  TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWIE);
}

void TWI_start() 
{
  TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
  while (!(TWCR & (1 << TWINT)));
 // while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement
}

void TWI_read_address(unsigned char data)
{
  TWDR=data;    // Address and read instruction
  TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
  while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
    //while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
} 

void TWI_stop() {
  TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
  while (TWCR & (1 << TWSTO));
}


void TWI_write_data(uint8_t data) 
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
   //while((TWSR & 0xF8) != 0x28); 
}
uint8_t TWI_read_data(void)
{
    uint8_t recv_data;
    TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
    while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
    //while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
    recv_data=TWDR;
    return recv_data;
}
void TWI_write_address(unsigned char data)
{
    TWDR = data;
    TWCR = (1 << TWINT) | (1 << TWEN);
    while (!(TWCR & (1 << TWINT)));
    //while((TWSR & 0xF8) != 0x18); 
}


void pca9685_set_pwm(uint8_t prescale_value){
  TWI_start();
  TWI_write_data(PCA9685_ADDRESS<<1);
  TWI_write_data(0xFE);
  TWI_write_data(prescale_value);
  TWI_stop();
}

uint8_t i2c_read_register(uint8_t register_address){
  uint8_t data;
  TWI_start();
  TWI_write_data(PCA9685_ADDRESS<<1);
  TWI_write_data(register_address);
  TWI_start();
  TWI_write_data(PCA9685_ADDRESS<<1 | 1);
  data=TWI_read_data();
  TWI_stop(); 
  return data;
}



void setup() {

  TWI_init_master();

  TWI_start();
  TWI_write_address(PCA9685_ADDRESS << 1);
  TWI_write_data(0x00);
  TWI_write_data(0x20);
  TWI_stop();

  TWI_start();
  TWI_write_address(PCA9685_ADDRESS << 1);
  TWI_write_data(0x01);
  TWI_write_data(0x04);
  TWI_stop();

  pca9685_set_pwm(39);
}

void loop() {

/*
  // put your main code here, to run repeatedly:
sendData = 79;
        // Inicia a comunicação I2C
TWI_start();

        // Envia o endereço do dispositivo escravo com o bit de escrita (0)
slaveAddress = 0x50;       
TWI_write_address(slaveAddress +write);

        // Envia os dados para o escravo
TWI_write_data(sendData);

        // Encerra a comunicação I2C
TWI_stop();

_delay_ms(500);






*/


TWI_start();

slaveAddress = 128;
uint8_t pca9685Address = 0x40;
TWI_write_address(pca9685Address << 1);
sendData=0x06;

uint8_t pwmChannel = 0;
TWI_write_data(0x06 + (4 * pwmChannel));

TWI_write_data(0 & 0xFF);

TWI_write_data(0>>8);

uint16_t dutyCycle = 2300; // Por exemplo, 50% de ciclo de trabalho
// Enviar os bytes de configuração do ciclo de trabalho (8 bits de ON e 8 bits de OFF)
TWI_write_data(dutyCycle & 0xFF);        // Byte ON_L
TWI_write_data(dutyCycle >>8); // Byte ON_H

TWI_stop();

_delay_ms(500);
}
