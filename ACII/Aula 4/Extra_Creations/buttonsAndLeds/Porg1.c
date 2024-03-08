#include <detpic32.h>
#define FREQ 80000000
#define PBCLK (FREQ/2)
#define NC (FREQ/4)

void delay(int x){
    resetCoreTimer();
    while (readCoreTimer() < x)
    {
        
    }
    
};

 int main(int argc, char const *argv[])
 {
    TRISE = 0xFF00;
    TRISB = 0X80FF;
    TRISDbits.TRISD8 = 1;
    LATE = 0X0000;
    
    while (1)
    {   
        int i = (unsigned int)NC>>(PORTB & 0x0007);
        
        if (PORTBbits.RB3 == 0)
        {   
            LATEbits.LATE0 = !PORTDbits.RD8;
            delay(i);
            LATE = LATE<<1;
        }else
        {
            LATEbits.LATE7 = !PORTDbits.RD8;
            delay(i);
            LATE = LATE>>1;
        }
        
        
        
        
    }

    return 0;
 }
 


 
