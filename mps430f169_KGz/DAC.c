#include <msp430f169.h>
//#define _USE_MATH_DEFINES
#include <math.h>

#define SAMPLE_RATE 10000    
#define SINE_FREQ 1000       
#define SAMPLES (SAMPLE_RATE/SINE_FREQ) 

volatile unsigned int sine_table[SAMPLES]; 

void init_DAC(void) {
    
    DAC12_0CTL = DAC12SREF_0 + DAC12IR + DAC12AMP_5 + DAC12ENC;
}

void generate_sine_table(void) {
    unsigned int i;
    for(i = 0; i < SAMPLES; i++) {
        
        sine_table[i] = 2048 + (int)(2047 * sin(6.283185307179586 * i / SAMPLES));
    }
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;  
    
   
    BCSCTL1 = RSEL0 + RSEL1 + RSEL2;
    DCOCTL = DCO0 + DCO1 + DCO2;
    
    
    ADC12CTL0 = REFON + REF2_5V;
    __delay_cycles(1000);  
    
    
    init_DAC();
    
    
    generate_sine_table();
    
    
    TA0CCR0 = (8000000/SAMPLE_RATE) - 1; 
    TA0CTL = TASSEL_2 + MC_1;  
    TA0CCTL0 = CCIE;           
    
    __enable_interrupt();       
    
    while(1) {
        __low_power_mode_0();  
    }
}


#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void) {
    static unsigned int index = 0;
    
    DAC12_0DAT = sine_table[index]; 
    index = (index + 1) % SAMPLES; 
}