#include <msp430f2001.h>

#define GREEN_LED (BIT6)

void delay(unsigned int t) {
    volatile unsigned int i;
    for (i = 0; i < t; i++);
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD; // Отключаем watchdog
    P1DIR = 0xFF;
   // P1DIR |= BIT6;        // Только P1.6 как выход
  //  P1OUT &= ~BIT6;       // Начальное состояние - выключен

    while(1) {
        P1OUT ^= BIT0;    
        delay(10000);        
        P1OUT ^= BIT1;    
        delay(10000); 
        P1OUT ^= BIT2;    
        delay(10000);        
        P1OUT ^= BIT3;    
        delay(10000);  
        P1OUT ^= BIT4;    
        delay(10000);        
        P1OUT ^= BIT5;    
        delay(10000);
        P1OUT ^= BIT6;    
        delay(10000);        
        P1OUT ^= BIT7;    
        delay(10000);       
    }
}