#include <detpic32.h>
#define FREQ 40000000
#define PBCLK (FREQ/2)
#define NC (FREQ/4096)

int main(int argc, char const *argv[])
{
    TRISCbits.TRISC14 = 0;
    while (1)
    {
        LATCbits.LATC14 = 1;
    }
    
    return 0;
}
