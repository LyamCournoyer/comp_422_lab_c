#include<avr/io.h>

#define DDR_SPI DDRB
#define DD_MOSI DDB3
#define DD_SCK DDB5
#define MYUBRR 103
void setup() {
  UBRR0H = (MYUBRR>>8);
  UBRR0L = MYUBRR;


  UCSR0C = 0x06;
  UCSR0B = (1<<RXEN0);
  UCSR0B|=(1<<TXEN0)|(1<<RXEN0); 
  DDRB |= (1 << 2);
  DDR_SPI |= (1 << SS);
  
  PRR &= ~(1 << PRSPI);
 
  DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);

  SPCR = (1<<SPE)|(1<<MSTR) | (1 << SPR0)| (1 << SPR1);

}

void loop() {  
    while ( !(UCSR0A & (1<<RXC0)) );
    char input = UDR0;  
    switch(input) 
      {
          case 'a' : 
                     writeSpi(0x61);
                     break;
          case '2' : 
                     writeSpi(0x32);
                     break;
           default  :                   
                     break;
     }  
}

void writeChar(char c){
   while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;
}

void writeSpi(uint8_t data)
{    
    SPDR = data;
    while(!(SPSR & (1 << SPIF)));
    char input = SPDR;
    writeChar(input);
}
