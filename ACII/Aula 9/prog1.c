#include <detpic32.h>
#include "../outils.c"
#define SAMPLE 16
#define RESOLUTION 500
#define PRINTRANGE 33

static int Converted_Value = 0;
static int Print_Value = 0;

void printConverted(){
    printInt(Converted_Value, 10 | 10 << 5);
        putChar('_');
        putChar('_');
        putChar('_');
        putChar('_');
        putChar('\r');    
}

int main(int argc, char const *argv[])
{   
    TRISE = TRISE & 0xFF00;
    displayInit();
    setDispVal(54);

    setAD1IF();
    setADC1Ch4RB4(SAMPLE);

    

    //Timer 1 config
    T1CONbits.TCKPS = 2;        // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR1 = 31249;                // Fout = 20MHz / (32 * (62499 + 1)) = 5 Hz
    TMR1 = 0;                   // Clear timer T1 count register
    T1CONbits.TON = 1;          // Enable timer T1 (must be the last command of the
                                // timer configuration sequence)
    //--------------------------//  
    IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1; // Enable timer T1 interrupts
    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag 
    //--------------------------//

    //Timer 3 config
    T3CONbits.TCKPS = 2;        // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR3 = 49999;                // Fout = 20MHz / (32 * (62499 + 1)) = 50 Hz
    TMR3 = 0;                   // Clear timer T3 count register
    T3CONbits.TON = 1;          // Enable timer T3 (must be the last command of the
                                // timer configuration sequence)
    //--------------------------//  
    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1; // Enable timer T3 interrupts
    IFS0bits.T3IF = 0; // Reset timer T3 interrupt flag 
    //--------------------------//

    T2CONbits.TCKPS = 5;        // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR2 = 62499;                // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR2 = 0;                   // Reset timer T2 count register
    T2CONbits.TON = 1;          // Enable timer T2 (must be the last command of the
                                // timer configuration sequence)
    OC1CONbits.OCM = 6;         // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL =0;       // Use timer T2 as the time base for PWM generation
    OC1RS = 12500;              // Ton constant
    OC1CONbits.ON = 1;          // Enable OC1 module 


    EnableInterrupts();
    while (1)
    {   
        
    }
    


    

    return 0;
}

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

    // Calculating average value
    // sending the value to main
    Converted_Value = (((accumulator+ SAMPLE/2)/SAMPLE)*RESOLUTION+512)/(1024);
    Print_Value = (((accumulator+ SAMPLE/2)/SAMPLE)*PRINTRANGE+512)/(1024);
    setDispVal(Print_Value);
    IFS1bits.AD1IF=0;
}


void _int_(4) isr_timer1(void){
    LATEbits.LATE1 = !LATEbits.LATE1;
    AD1CON1bits.ASAM = 1;

    printConverted();

    IFS0bits.T1IF = 0; // Reset timer T1 interrupt flag 
}


void _int_(12) isr_timer3(void){
    LATEbits.LATE3 = !LATEbits.LATE3;

    displayToggle();
    
    IFS0bits.T3IF = 0; // Reset timer T1 interrupt flag 
}
