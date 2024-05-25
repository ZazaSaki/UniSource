#include <detpic32.h>
#define PBCLK 20000000
#define BRF 16
#define BR 115200
#define BRG ((PBCLK +(BRF/2)*BR)/(BRF*BR)-1)
#define FRAMERATE PBCLK/120

#include "../outils.c"

void puttc(char);
char gettcU2(void);
char gettChillC(void);
void putString(char*);

int main(int argc, char const *argv[])
{
    // // Configure UART2:
    // // 1 - Configure BaudRate Generator x
    // U2BRG = BRG; // BoadRate
    // U2MODEbits.BRGH = 0; // 1/0 4x/16x

    // // 2 – Configure number of data bits, parity and number of stop bits
    // // (see U2MODE register) x
    // U2MODEbits.PDSEL = 0; // 00/01/10/11 none/par/odd/9None
    // U2MODEbits.STSEL = 0; // 1 or 0

    // // 3 – Enable the trasmitter and receiver modules (see register U2STA) x
    // U2STAbits.UTXEN = 1; // 1/0 on/off
    // U2STAbits.URXEN = 1; // 1/0 on/off
    // // 4 – Enable UART2 (see register U2MODE) 
    // U2MODEbits.ON = 1;

    initUART2(BRG, 'N',8,1);

    displayInit();

    TRISE = 0xFF00;
    LATE = 0xFF00;
    
    char c = NULL;
    char d = NULL;

    while (1)
    {
       char c = gettChillC();

       sendToDisp(d&0xff,FRAMERATE);
       puttcU2(c);
       //LATEbits.LATE1 = !LATEbits.LATE1;
       
       if (c!=NULL)
       {
        d=c;
        LATE = 0x00FF & c;
        if (c == 0x0A)
        {   
            char *string = "EEEEEEE";
            putStringU2(string);
        }
        
       }
       
       
    }
    

    return 0;
}


// void puttc(char byte2send)
// {
//     // wait while UTXBF == 1
//     while (U2STAbits.UTXBF == 1);
//     // Copy byte2send to the UxTXREG register
//     U2TXREG = byte2send;
    
// } 

// char gettc(void)
// {
//     // If OERR == 1 then reset OERR
//     if (U2STAbits.OERR == 1)
//     {
//         U2STAbits.OERR = 0;
//     }
    
//     // Wait while URXDA == 0
//     while (U2STAbits.URXDA == 0);
    
//     return U2RXREG;
    
//     // Return UxRXREG
// } 


// char gettChillC(void){
//     // If OERR == 1 then reset OERR
//     if (U2STAbits.OERR == 1)
//     {
//         U2STAbits.OERR = 0;
//     }
    
//     // Wait while URXDA == 0
//     if (U2STAbits.URXDA != 0){
//         return U2RXREG;
//     };

//     return NULL;
// }

// void putString(char* string){
//     char *p = string;

//     while (*string != '\0')
//     {   
//         puttc(*string);
//         string++;

               
//     }
    
// }