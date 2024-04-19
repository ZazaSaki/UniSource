#include <detpic32.h>;
#define FREQ 40000000;
#define PBCLK FREQ/2
#define FREQ4 PBCLK*10/46;
#define FREQ7 PBCLK*10/76;


int main()
{
    TRISD = TRISD & 0XFF03; // 1111 1111 0000 0011
    TRISB = TRISB | 0x0006;
    LATE = 0x00FC;

    delayVal = FREQ7

    while (1)
    {
        if (PORTBbits.RB2 & PORTBbits.RB3)
        {
            delayVal = FREQ7;
        }

        if (!PORTBbits.RB2 & !PORTBbits.RB3)
        {
            delayVal = FREQ4;
        }
        
        delay(delayVal)


    }
    

    return 0;
}


int delay(int time){
    reserCoreTimer()
    while (readCoreTimer < time);
    
};
