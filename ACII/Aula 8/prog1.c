#include <detpic32.h>
#include "../outils.c"

#define FREQ 40000000
#define PBCLK FREQ/2
#define SAMPLE 2
#define RESOLUTION PBCLK/500

static int i = 0;

void _int_(27) isr_adc(void){

    putChar('\r');
    
    int accumulator = 0;
    int *p = (int *)(&ADC1BUF0);
    

    //reading buffer
    for(; p <= (int *)(&ADC1BUF0 + SAMPLE*4); p+=4 ) {
        // putChar('_');
        // printInt(*p, 10 | 3 << 10) ;
        // putChar(':');
        // putChar(':');
        // putChar(':');
        accumulator += *p;
    }    
    
    printInt(accumulator, 10 | 3 << 10) ;
    putChar(':');

    printInt(SAMPLE, 10 | 3 << 10) ;
    putChar(':');

    // Calculating average value
    // sending the value to main
    i = (((accumulator+ SAMPLE/2)/SAMPLE)*RESOLUTION+512)/(1024);
    printInt(i, 10 | 3 << 10) ;
    putChar(':');
    
    
    IFS1bits.AD1IF=0;
}



int main(int argc, char const *argv[])
{
    DisableInterrupts();
    setAD1IF();
    setADC1Ch4RB4(SAMPLE);
    
    
    
    TRISB = TRISB & 0X80FF;
    TRISE = 0xFF00;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATE = 0X0000;
    
    EnableInterrupts(); // Macro defined in "detpic32.h" 
    while (1)
    {
        
        AD1CON1bits.ASAM = 1; 
        DisableInterrupts();
        sendToDisp10(45,i);
        displayOff();    
        EnableInterrupts();

    }
    


    return 0;
}


