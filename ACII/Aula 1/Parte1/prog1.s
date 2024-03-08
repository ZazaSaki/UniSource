    .data
    .equ ADDR_BASE_HI,0xBF88
    .equ TRISB, 0x6040
    .equ PORTB, 0x6050
    .equ LATB, 0x6060
    .equ TRISE, 0x6100
    .equ PORTE, 0x6110
    .equ LATE, 0x6120
    .equ TRISD, 0x60C0
    .equ PORTD, 0x60E0
    .equ LATD, 0x60D0
    .text
    .globl main

main:
    lui $t0, ADDR_BASE_HI

    lw $t1, TRISB($t0)
    ori $t1, $t1, 0xFFFF

    sw $t1, TRISB($t0)

    lw $t1, TRISE($t0)
    andi $t1, $t1, 0xFFF0

    sw $t1, TRISE($t0)

    li $t1,0xFFFF
    sw $t1,TRISD($t0)



while:

    #lw $t1, PORTB($t0)
    #andi $t1, $t1, 0x000F

    lw $t2, LATE($t0)
    #andi $t2, $t2, 0xFFF0
    #or $t2, $t2, $t1
    ori $t2, $t2, 0x000F
    

    lw $t3,LATD($t0)
if:    andi $t3,0x0100


    bne $t3,0x0100,endIf

endIf:
    ori$


    sw $t2, LATE($t0)
    j while

    jr $ra