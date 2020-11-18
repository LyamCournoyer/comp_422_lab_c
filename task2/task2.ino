#include<avr/io.h>


#define MYUBRR 103
#define CHUNK 5
#define MAXCHAR 40
#define TERMINATOR '\n'
void setup() {
  
  UBRR0H = (MYUBRR>>8);
  UBRR0L = MYUBRR;

  UCSR0C = 0x06;
//  UCSR0B = (1<<RXEN0);
  UCSR0B = (1<<TXEN0)|(1<<RXEN0); 
  

}

void loop() {  
  
  char * name_;
  char * greeting = "hello ";
  char * prompt = "Enter name. Terminate with newline \n";
  writeString(prompt);
  name_ = readName();
  writeString(greeting);
  writeString(name_);
  writeChar(TERMINATOR);
  free(name_);
}

void writeChar(char c){
   while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = c;
}

char * readName(void){   
   char *name_ = NULL, *tmp = NULL;
   size_t size = 0, idx = 0;   
//   char name[40];
   while(1){
     while ( !(UCSR0A & (1<<RXC0)) );
     char input = UDR0;    
     
     if (idx >= MAXCHAR){
        USART_Flush();
        break;
     }
     if (input == TERMINATOR){
        name_[idx] = '\0';
        break;
     }
      if (size <= idx) {
            size += CHUNK;
            tmp = realloc(name_, size);
            if (!tmp) {
                free(name_);
                name_ = NULL;
                break;
            }
            name_ = tmp;
        }
     name_[idx++] = input;
     
  }
  
  return name_;
}

void writeString( char * string){
  size_t i = 0;
  while (string[i] != '\0') {       /* Stop looping when we reach the null-character. */
   writeChar(string[i]);    /* Print each character of the string. */    
    i++;
  }
}


void USART_Flush( void ){
  unsigned char dummy = 'a';
  while(dummy != TERMINATOR){
      while ( UCSR0A & (1<<RXC0) ){
      dummy = UDR0;
      }
    }
}
   
  
