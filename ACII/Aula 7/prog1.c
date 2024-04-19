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
    IPC6bits.AD1IP = 2; // configure priority of A/D interrupts 
    IFS1bits.AD1IF = 0; // clear A/D interrupt flag 
    IEC1bits.AD1IE = 1; // enable A/D interrupts 
    

    TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RB4 configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = SAMPLE-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace 4 by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    
    
    
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


