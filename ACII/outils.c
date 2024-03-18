#include <detpic32.h>
//Agrressive delay
    void delay(int x){
        resetCoreTimer();
        while (readCoreTimer() < x)
        {
            
        }
        
    };

// soft delay
    int delay_conter_for_own_timer = 0;
    int chill_delay(int x){
        if (delay_conter_for_own_timer < x)
        {
            delay_conter_for_own_timer++;
            return 0;
        }else
        {
            delay_conter_for_own_timer = 0;
            return 1;
        }
        
        
    }

//dysplay defaults
    //TRISB = TRISB & 0X80FF; 

    //Display Values
        static const unsigned char Disp7Seg[] =  {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E,  0x79, 0x71};

    
    //Display Char 
        // int DispL(char c){
        //     if (c>47 && c<58){
        //         return DispLN(c-48);
        //     }

        //     if (c>64 && c < 71){
        //         return DispLN(c-55);
        //     }

        //     switch (c)
        //     {
        //     case 'º':
        //         return DispLN(0x10);
            
        //     default:
        //         break;
        //     }
            
        //     return 0x0;
        // }

    //Display int
        int DispLN(int i){

            return Disp7Seg[i]<<8;

        }

    //send vals
        void Dysp(int val,int prt){
            if (val == 0)
            {
                LATB = (LATB & 0X80FF) | prt;
                LATDbits.LATD5 = 1;
                LATDbits.LATD6 = 0;
            }else
            {
                LATB = (LATB & 0X80FF) | prt;
                LATDbits.LATD5 = 0;
                LATDbits.LATD6 = 1;
            }
            
                
            
        }


        void displayOff(void){
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 0;
        }

        void sendToDisp(int val, int clk){
            Dysp(0, DispLN(val & 0xF));
            delay(clk);
            Dysp(1, DispLN((val & 0xF0)>>4));
            delay(clk);
        }

        void sendToDisp10(int val, int clk){
            Dysp(0, DispLN((val%10) & 0xF));
            delay(clk);
            Dysp(1, DispLN((val/10) & 0xF));
            delay(clk);
        }       
 