    .data
    .equ ADDR_BASE_HI , 0xBF88
    .equ TRISE , 0x6100
    .equ LATE , 0x6120


    .text
    .globl main


# t3 = counter 
# s0 = ADDr_BASE_HI
main:
    # loding last code line id
    addiu $sp, $sp, -4
    sw    $ra, 0($sp)
    
    
    # load important variables
    # using s reg to save var from callee's
    lui $s0 , ADDR_BASE_HI
    
    # Configuration of ports E as outputs
    lw $t1 , TRISE($s0)
    andi $t1 , $t1 , 0xFF00
    sw $t1 , TRISE($s0)


    # inicializing counter
    li $t3, 0
While:  

    # calling delay(40)
    li $a0, 4000000
    jal delay

    # incrementing counter
    addi $t3, $t3, 1

    # Showing on leds
    sw $t3, LATE($s0)

    j While


    # loding last code line id
    lw    $ra, 0($sp)
    addiu $sp, $sp, 4

    li $v0, 0
    jr $ra



# t1 = delay counter 
delay : 
    # inicializing conuter
    li $t1, 0
whDelay :
    # incrementing counter
    addi $t1, $t1, 1

    # checking if is finishde
    blt $t1 , $a0, whDelay

    # returning to caller(in this case is main function)
    jr $ra



