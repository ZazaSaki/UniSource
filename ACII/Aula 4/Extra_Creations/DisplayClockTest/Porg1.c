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
    
        
    
//}

void UpdateDefaults(){
    
}


 int main(int argc, char const *argv[])
 {
    TRISE = 0xFF00;
    TRISB = 0X80FF;
    TRISDbits.TRISD8 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD6 = 0;
    LATE = 0X0000;
    
    //Way 3
    setDispVal(45);
    
    //Way 1
    int ch1 = DispLN(4);
    int ch2 = DispLN(5);

    while (1)
    {   
        
        int i = (PORTB & 0x000F)<<8;
        

        
        //Way 1
        // Dysp(0,ch1);
        // delay(i);
        // Dysp(1,ch2);
        // delay(i);
        
        
        //Way 2
        //Dysp10(0, 45);
        // delay(i);
        //Dysp10(1,45);
        // delay(i);
        
        //Way 3
        displayToggle();
        delay(i);
        displayToggle();
        delay(i);
       



        
        
        
    }

    return 0;
 }
 


 
