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
        int DispL(char c){
            
            switch (c)
            {
            case '0':
                return Disp7Seg[0x0];
            case '1':
                return Disp7Seg[0x1];
            case '2':
                return Disp7Seg[0x2];
            case '3':
                return Disp7Seg[0x3];
            case '4':
                return Disp7Seg[0x4];
            case '5':
                return Disp7Seg[0x5];
            case '6':
                return Disp7Seg[0x6];
            case '7':
                return Disp7Seg[0x7];
            case '8':
                return Disp7Seg[0x8];
            case '9':
                return Disp7Seg[0x9];
            case 'A':
                return Disp7Seg[0xA];
            case 'B':
                return Disp7Seg[0xB];
            case 'C':
                return Disp7Seg[0xC];
            case 'D':
                return Disp7Seg[0xD];
            case 'F':
                return Disp7Seg[0xE];
            case 'E':
                return Disp7Seg[0xF];
            case 'º':
                return Disp7Seg[0x10];
            
            default:
                break;
            }
            
        }

    //Display int
        int DispLN(int i){

            return Disp7Seg[i]<<8;

            // switch (i)
            // {
            //     case 0x0:
            //         return s0;
            //     case 0x1:
            //         return s1;
            //     case 0x2:
            //         return s2;
            //     case 0x3:
            //         return s3;
            //     case 0x4:
            //         return s4;
            //     case 0x5:
            //         return s5;
            //     case 0x6:
            //         return s6;
            //     case 0x7:
            //         return s7;
            //     case 0x8:
            //         return s8;
            //     case 0x9:
            //         return s9;
            //     case 0xA:
            //         return sA;
            //     case 0xB:
            //         return sB;
            //     case 0xC:
            //         return sC;
            //     case 0xD:
            //         return sD;
            //     case 0xF:
            //         return sF;
            //     case 0xE:
            //         return sE;
                
            //     default:
            //         return 0x0000;
            // }   
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
 