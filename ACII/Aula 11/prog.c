#include <detpic32.h>
#define BDRT 115200

#include "../outils.c"

int main(){   
    //Mode Config
    U1MODEbits.BRGH = ((PBCLK + 8*BDRT)/(16*BDRT)) - 1;
    U1MODEbits.PDSEL= 0;
    U1MODEbits.STSEL= 0;

    //Status Config
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;

    //open gate
    U1MODEbits.ON = 1;

    //interruption
    IPC6bits.U1IP = 2;
    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;

    IEC0bits.U1TXIE = 0;
    //IEC1bits.U2EIE = 0;

    EnableInterrupts();
    while (1)
    {
        
    }
    
    
    return 0;
}

void _int_(24) uart2Int(void){
    
    if (IFS0bits.U1RXIF == 1)
    {
        puttcU1(gettcU1());
        IFS0bits.U1RXIF = 0;
    
    }
    
    
    
}


