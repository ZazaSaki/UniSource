#include <detpic32.h>
#define FREQ 40000000
#define PBCLK (FREQ/2)
#define NC (FREQ/2)

#include "../../../outils.c"

// void Dysp(int val,int prt){
//     if (val == 0)
//     {
//         LATB = (LATB & 0X80FF) | prt;
//         LATDbits.LATD5 = 1;
//         LATDbits.LATD6 = 0;
//     }else
//     {
//         LATB = (LATB & 0X80FF) | prt;
//         LATDbits.LATD5 = 0;
//         LATDbits.LATD6 = 1;
//     }
    
        
    
// }

void UpdateDefaults(){
    
}


 int main(int argc, char const *argv[])
 {
    TRISE = 0xFF00;
    TRISB = 0X80FF;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATE = 0X0000;
    
    
    while (1)
    {   
        

        int i = PORTB & 0x000F;
        Dysp(0,DispLN(i));
        delay(512);
        Dysp(1,DispLN(0x000F-i));
        delay(512);


        
        
        
    }

    return 0;
 }
 


 
