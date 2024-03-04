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
    TRISD = TRISD & 0X80FF;

    //Display Values
        #define s0 0x3F00
        #define s1 0x0600
        #define s2 0x5B00
        #define s3 0x4F00
        #define s4 0x6600
        #define s5 0x6D00
        #define s6 0x7D00
        #define s7 0x0700
        #define s8 0x7F00
        #define s9 0x6F00
        #define sE 0x7900
        #define sA 0x7700
        #define sB 0x7C00
        #define sC 0x3900
        #define sD 0x5E00
        #define sF 0x7100

    
    //Display Char 
        int DispL(char c){
            
            switch (c)
            {
            case '0':
                return s0;
            case '1':
                return s1;
            case '2':
                return s2;
            case '3':
                return s3;
            case '4':
                return s4;
            case '5':
                return s5;
            case '6':
                return s6;
            case '7':
                return s7;
            case '8':
                return s8;
            case '9':
                return s9;
            case 'A':
                return sA;
            case 'B':
                return sB;
            case 'C':
                return sC;
            case 'D':
                return sD;
            case 'F':
                return sF;
            case 'E':
                return sE;
            case 'º':
                return s0;
            
            default:
                break;
            }
            
        }

    //Display int
        int DispLN(int i){
            switch (i)
            {
                case 0x0:
                    return s0;
                case 0x1:
                    return s1;
                case 0x2:
                    return s2;
                case 0x3:
                    return s3;
                case 0x4:
                    return s4;
                case 0x5:
                    return s5;
                case 0x6:
                    return s6;
                case 0x7:
                    return s7;
                case 0x8:
                    return s8;
                case 0x9:
                    return s9;
                case 0xA:
                    return sA;
                case 0xB:
                    return sB;
                case 0xC:
                    return sC;
                case 0xD:
                    return sD;
                case 0xF:
                    return sF;
                case 0xE:
                    return sE;
                
                default:
                    return 0x0000;
            }   
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

        void sendToDisp(int val){
            Dysp(val & 0x0F, 0);
            delay(521);
            Dysp(val & 0xF0>>4, 1);
        }        