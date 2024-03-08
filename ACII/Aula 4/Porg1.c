#include <detpic32.h>
#define FREQ 40000000
#define PBCLK (FREQ/2)
#define NC (FREQ/4096)

#include "../outils.c"

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

// void sendToDisp(int val){
//     Dysp(val & 0x0F, 0);
//     delay(521);
//     Dysp(val & 0xF0>>4, 1);
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
    
    int i = 0;
    while (1)
    {   
        
        int DisplayClock = ((PORTB & 0x000F)<<6)+0x0001; //controlling the refesh rate through the siwtches
        int val = (PORTB & 0x000F)>>2;
        
        Dysp(0,DispLN(i));
        delay(DisplayClock);
        Dysp(1,DispLN(0x000F-i));
        delay(DisplayClock);

        if (chill_delay(NC<<(4-val)) && PORTDbits.RD8) //balancing the counting rate (Δ_count_rate = 1/Δ_refresh_rate)
        {
            i++;
            if(i>0xF){
                i=0;
            }
        }
        


        
        
        
    }

    return 0;
 }
 


 
