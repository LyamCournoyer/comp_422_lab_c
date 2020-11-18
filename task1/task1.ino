#include<avr/io.h>


#define MYUBRR 103
void setup() {
  UBRR0H = (MYUBRR>>8);
  UBRR0L = MYUBRR;


  UCSR0C = 0x06;
  UCSR0B = (1<<RXEN0);
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0); 
  DDRB |= (1 << 5);

}

void loop() {
    while ( !(UCSR0A & (1<<RXC0)) );
    char input = UDR0;        
    switch(input) 
      {
          case 'a' : PORTB |= (1<<5);                                  
                     break;
          case '2' : PORTB &= ~(1<<5);
                     break;
           default  :                   
                     break;
     }
}
