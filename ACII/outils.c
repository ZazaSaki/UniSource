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
        static int _reserved_display_val_0 = 88;
        void setDispVal(int i){
            _reserved_display_val_0 = i;
            
        }
        void displayInit(void){
            TRISB = TRISB & 0x80FF;
            TRISDbits.TRISD5 = 0;
            TRISDbits.TRISD6 = 0;
        }

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

        void Dysp10(int val,int prt){
            int show = 0;
            if (val == 0)
            {   
                show = DispLN((prt%10) & 0xF);
            }else
            {   
                show = DispLN((prt/10) & 0xF);
            }
            
            Dysp(val, show);
        }



        void displayOff(void){
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 0;
            
        }

        void displayToggle(void){
            Dysp10(!LATDbits.LATD6, _reserved_display_val_0);
            
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
 

// ADC1

    // Set Converter
    void setADC1Ch4RB4(int sample){
        TRISBbits.TRISB4 = 1; // RB4 digital output disconnected
        AD1PCFGbits.PCFG4= 0; // RB4 configured as analog input
        AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
        // mode an internal counter ends sampling and
        // starts conversion
        AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
        // interrupt is generated. At the same time,
        // hardware clears the ASAM bit
        AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
        AD1CON2bits.SMPI = sample-1; // Interrupt is generated after N samples
        // (replace N by the desired number of
        // consecutive samples)
        AD1CHSbits.CH0SA = 4; // replace 4 by the desired input
        // analog channel (0 to 15)
        AD1CON1bits.ON = 1; // Enable A/D converter
        // This must the last command of the A/D
        // configuration sequence
    }

    void setAD1IF(){
        IPC6bits.AD1IP = 2; // configure priority of A/D interrupts 
        IFS1bits.AD1IF = 0; // clear A/D interrupt flag 
        IEC1bits.AD1IE = 1; // enable A/D interrupts 
    }