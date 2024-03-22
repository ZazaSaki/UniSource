#include <detpic32.h>
#include "../outils.c"

#define SAMPLES 16

int main(int argc, char const *argv[])
{
    // TRISBbits.TRISB4 = 1;
    // AD1PCFGbits.PCFG4 = 0;

    // AD1CHSbits.CH0SA = 4;

    // AD1CON1bits.ASAM = 1;

    TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RB4 configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = SAMPLES-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace 4 by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequence
    
    EnableInterrupts();
    
    TRISB = TRISB & 0X80FF;
    TRISE = 0xFF00;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATE = 0X0000;
    int c = 0;
    int i = 0;
    int accumulator = 0;
    int res = 33;
    while (1)
    {
        AD1CON1bits.ASAM = 1; 
        if (PORTDbits.RD8 == 0)
        {
            c=0;
        }
        
        while(IFS1bits.AD1IF == 0){
            

            if (PORTDbits.RD8 != 0 & c <84)
            {
                c++;
            }
        };
            
        
        
        printInt(c, 10 | 3 << 10) ;

        putChar('_') ;
        printInt(PORTDbits.RD8, 10 | 3 << 10) ;
        

        int *p = (int *)(&ADC1BUF0);
        for(; p <= (int *)(&ADC1BUF0 + SAMPLES*4); p+=4 ) {
            putChar('_');
            printInt(*p, 10 | 3 << 10) ;

            accumulator += *p;
        }    


        accumulator = (accumulator/SAMPLES+512)*res/1024;

        putChar('_') ;
        putChar('_') ;
        putChar('_') ;
        printInt(accumulator, 10 | 3 << 10) ;

        putChar('_') ;
        putChar('_') ;
        putChar('_') ;
        
        putChar('\r');
        putChar('\r');
        putChar('\r');
        putChar('\r');

        IFS1bits.AD1IF = 0;
        //delay(i);
        //sendToDisp10(45,i);




        
        
        

    }
    


    return 0;
}


