#include <detpic32.h>
#define FREQ 40000000
#define PBCLK (FREQ/2)
#define NC ((FREQ/2048)>>2)
#define LIM 0xFF

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
    
    int i = 0;
    while (1)
    {   
        

        
        sendToDisp10(i,512);
        // Dysp(0,DispLN(i));
        // delay(512);
        // Dysp(1,DispLN(LIM-i));
        // delay(512);

        if (chill_delay(NC))
        {
            i++;
            if(i>LIM){
                i=0;
            }
        }
        


        
        
        
    }

    return 0;
 }
 


 
