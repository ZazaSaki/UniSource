    .data
    .equ ADDR_BASE_HI,0xBF88 # Base address: 16 MSbits
    .equ TRISE,0x6100 # TRISE address is 0xBF886100

    .equ TRISB,0x6040 # TRISE address is 0xBF886040
    .equ PORTB,0x6050 # PORTE address is 0xBF886040

    .equ PORTE,0x6110 # PORTE address is 0xBF886110
    .equ LATE,0x6120 # LATE address is 0xBF886120
    .equ freqOn,1
    .equ freqOff,20

    .equ TRISD, 0x60C0
    .equ PORTD, 0x60D0
    .text
    .globl main

main: 
    addi $sp,-4
    sw   $ra,0($sp)

    lui $t1,ADDR_BASE_HI    # $t1=0xBF880000
    #// carregar endereço base
    
    lw $t2,TRISE($t1)       # READ (Mem_addr = 0xBF880000 + 0x6100)
                            # //carregar valor da memoria
    andi $t2,$t2, 0xFF00    # MODIFY (bit0=bit3=0 (0 means OUTPUT))
                            # // forçar bit0 e bti3 a 0
    sw $t2,TRISE($t1)       # WRITE (Write TRISE register)
                            # //escrever devolta name "read modify write"


    lw $t2,TRISB($t1)       # READ (Mem_addr = 0xBF880000 + 0x6100)
                            # //carregar valor da memoria
    andi $t2,$t2, 0xFFFF    # MODIFY (bit0=bit3=0 (0 means OUTPUT))
                            # // forçar bit0 e bti3 a 0
    sw $t2,TRISB($t1)       # WRITE (Write TRISE register)
                            # //escrever devolta name "read modify write"

    li $t2, 0xFFFF
    sw $t2, TRISD($t1)      # set RD8 to output


loop:
    li $a0,'\r'
    li $v0,3    
    syscall     #  putChar('\r'); // cursor regressa ao inicio da linha no ecrã
    
    ori $a0,$0, 0xFFF0    # MODIFY (bit0 = 0)
     jal ligth_off

     sll $a0,$t5,1            # wait 1 sec
     jal delay

    ori $a0,$0, 0x000F     # MODIFY (bit3 = 1)
                             # // forçar bit0 e bti3 a 1
     jal ligth_on


     li $a0, freqOn            # wait 1 sec
     jal delay

    
    
                            #// carregar endereço base
    lw $t2,PORTB($t1)       # READ (Mem_addr = 0xBF880000    + 0x6050)
                            # //carregar valor da memoria

    li $a1,0x00020010
    andi $a0,$t2,0x000F
    move $t5,$a0
    sll $a0,$a0,4
    li $v0, 6   
    syscall     #  printInt(counter2, 10 | 4 << 16); 


    lw $t2,LATE($t1)        # READ (Read LATE register)
                            # // forçar bit0 e bti0 a 0
    lw $t3,PORTD($t1)
    andi $t3, 0x0100
    beq $t3,$0, nn
    li $t3,0x0000
    j nn2
nn:
    xori $t3,$t3,0xFFFF
nn2:
    ori $t2,$t2,0x00F0
    and  $a0,$a0,$t3
    ori $a0,$a0,0xFF0F
    and   $a0,$t2,$a0     # MODIFY (bit3 = 1)
                            # // forçar bit0 e bti3 a 1
    sw $a0,LATE($t1)        # WRITE (Write LATE register) 

    li $a1,0x00080002
    li $v0, 6   
    syscall     #  printInt(counter2, 10 | 4 << 16); 

    li $a1,0x00040010
    move $a0,$t3
    li $v0, 6   
    syscall     #  printInt(counter2, 10 | 4 << 16); 

    j loop
    
    lw   $ra,0($sp)
    addi $sp,4

    jr $ra



delay:
    li $v0,12
    syscall     #  resetCoreTimer();
    
    mul $a0,$a0,20000
   
WhDl:     
    li $v0,11
    syscall             
    blt $v0,$a0,WhDl
    jr $ra

ligth_on: 
    
                            #// carregar endereço base
    lw $t2,LATE($t1)        # READ (Read LATE register)
                            # // forçar bit0 e bti0 a 0
    or $t2,$t2,$a0     # MODIFY (bit3 = 1)
                            # // forçar bit0 e bti3 a 1
    sw $t2,LATE($t1)        # WRITE (Write LATE register) 
    jr $ra


ligth_off: 
    
                            #// carregar endereço base
    lw $t2,LATE($t1)        # READ (Read LATE register)
                            # // forçar bit0 e bti0 a 0
    and $t2,$t2, $a0     # MODIFY (bit3 = 1)
                            # // forçar bit0 e bti3 a 1
    sw $t2,LATE($t1)        # WRITE (Write LATE register) 
    jr $ra


set_ligth: 
    sw $a0,LATE($t1)        # WRITE (Write LATE register) 
    jr $ra


