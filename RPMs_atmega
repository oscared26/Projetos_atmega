#include <avr/interrupt.h>
#include <stdint.h>
#include <avr/io.h>

uint8_t numeroBinario = 0b00000000;
int unidades=0,dezenas=0,contador=0, centenas=0;

int pino_dez=2;
int pino_uni=3;
int c1;
int rpm=0;  

void calcularDisplay(int valor){

  c1=valor%100;
  centenas=valor/100;
  unidades=c1%10;
  dezenas=c1/10;

  for(int i=0;i<4;i++){
    PORTC=0b000001;
    numero_to_display(unidades); 
    delayMicroseconds(50); 
    PORTC=0b000010;
    numero_to_display(dezenas);
    delayMicroseconds(50); 
    PORTC=0b000100;
    numero_to_display(centenas);
    delayMicroseconds(50); 
  }
  EIMSK |= (1 << INT0);
}


ISR(INT0_vect) {
  //PORTB^=(1<<PB0);
	contador++;
}
ISR(TIMER1_OVF_vect) {
  EIMSK &= ~(1 << INT0);
  //PORTB^=(1<<PB0);
	TCNT1 = 0xC2F7;
  rpm=contador*3;

	contador=0; 
  
}

void setup() {
  // Configura os pinos de 0 a 7 como saídas (PORTD)
  DDRD=0b11110000;
  // Configura os pinos de 8 a 13 como saídas (PORTB)
  DDRB = 0b11111111;
  DDRC = 0b011111;

  PORTB=0;

	TCCR1A = 0b00000000; 
	TCCR1B = 0b00000101;
	TIMSK1 = 0b00000001;
	TCNT1 = 0xC2F7;


  // Configurar INT0 para acionar a interrupção em borda de subida
	EICRA=0b00000011;
	// Habilitar a interrupção no pino INT0
	EIMSK=0b00000001;
  // Habilitar interrupções globais
  sei();

  //Serial.begin(9600);
}

void loop() {


   calcularDisplay(rpm);
}

void numero_to_display(int numero)
{
   switch(numero){
     case 0:   
        PORTD=0b00000000;
	      PORTB=0b00001100;
	       break;
     case 1:   
        PORTD=0b10010000;
	      PORTB=0b00001111;
	       break;
     case 2:   
          PORTD=0b01000000;
	        PORTB=0b00001010;
	       break;
     case 3:   
          PORTD=0b00000000;
	        PORTB=0b00001011;
	       break;
     case 4:   
        
          PORTD=0b10010000;
	        PORTB=0b00001001;
	       break;

     case 5:   
          PORTD=0b00100000;
	        PORTB=0b00001001;
	       break;
     case 6:   
          PORTD=0b00110000;
	        PORTB=0b00001000;
	       break;
     case 7:   
          PORTD=0b10000000;
	        PORTB=0b00001111;
	       break;
     case 8:   
          PORTD=0b00000000;
	        PORTB=0b00000000;
	       break;
     case 9:   
          PORTD=0b10000000;
	        PORTB=0b00001001;
	       break;
     default:  
          PORTD=0b00000000;
	        PORTB=0b00000000;
   }

}
