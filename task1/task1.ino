#include<avr/io.h>

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR 103
void setup() {
  UBRR0H = (MYUBRR>>8);
  UBRR0L = MYUBRR;

//  UCSR0C = (0<<USBS0)|(3<<UCSZ00);
UCSR0C = 0x06;
    UCSR0B = (1<<RXEN0);
   UCSR0B|=(1<<TXEN0)|(1<<RXEN0); 
  DDRB |= (1 << 5);
  
Serial.begin(9600);
}

void loop() {
  while(1){
    while ( !(UCSR0A & (1<<RXC0)) );
    char input = UDR0;
  //  PORTB |= (1<<5);
  //  if(input == '\n')
  //     Serial.println("new");
  //    
  //  else
  //    Serial.println(input);
  //  delay(100);
  //  Serial.println("test");
  //  delay(100);
    
    
    switch(input) // using the switch() statement to  control the LED and Buzzer
      {
          case 'a' : PORTB |= (1<<5);                                  
                     break;
          case '2' : PORTB &= ~(1<<5);
                     break;
           default  :                   
                     break;
     }
  }

}
//void UART_getLine(char* buf, uint8_t n)
//{
//    uint8_t bufIdx = 0;
//    char c;
//
//    // while received character is not carriage return
//    // and end of buffer has not been reached
//   
//        // receive character
//        c = UART_getc();
//
//        // store character in buffer
//        buf[bufIdx++] = c;
//    }
//    while((bufIdx < n) && (c != '\r'));
//
//    // ensure buffer is null terminated
//    buf[bufIdx] = 0;
//}
//
//void UART_getc(void)
//{
//    // wait for data
//    while(!(UCSR0A & (1 << RXC0)));
//
//    // return data
//    return UDR0;
//}
