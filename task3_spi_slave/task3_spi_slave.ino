#include<avr/io.h>
#define DDR_SPI DDRB
#define DD_MISO DDB4
#define LEDPOS 5
void setup() {
  DDRB |= (1 << LEDPOS);
  DDR_SPI |= (1<<DD_MISO);
  SPCR = (1<<SPE);
  SPI_SlaveReceive();
}

void loop() {

     char input = SPI_SlaveReceive();
     switch(input) 
      {
          case 0x61: PORTB |= (1<<LEDPOS);                                  
                     break;
          case 0x32: PORTB &= ~(1<<LEDPOS);
                     break;
           default  :                                 
                     break;
     }

}


char SPI_SlaveReceive(void){
  while(!(SPSR & (1<<SPIF)));
  return SPDR;
}
