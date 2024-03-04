.data

.text
.globl main


main:           # int main(void)
    addiu $sp,$sp,-4
    sw  $ra,0($sp)

                # {
    li $t0,0    #  int counter = 0;
    li $t1,0    #  int counter1 = 0;
    li $t2,0    #  int counter2 = 0;

    
    li $t4,0
    li $t6,0
while:          #  while(1)
                #  {

    li $a0,'\r'
    li $v0,3    
    syscall     #  putChar('\r');

    # print Counters
    li $a1,0x0004000A
    move $a0,$t0
    li $v0,6   
    syscall     #  printInt(counter, 10 | 4 << 16);
    
    jal chln

    li $a1,0x0004000A
    move $a0,$t1
    li $v0, 6   
    syscall     #  printInt(counter1, 10 | 4 << 16);

    jal chln

    li $a1,0x0004000A
    move $a0,$t2
    li $v0, 6   
    syscall     #  printInt(counter2, 10 | 4 << 16); 


    
    li $a0,100
    jal delay # delay(100)//10Hz
    
    addi $t0,$t0,1     #  counter++;
    addi $t4,$t4,1     #  counter++;
    
    blt  $t4,2,endCheck
        addi $t1,$t1,1
        li $t4,0
        addi $t6,$t6,1
    
endCheck:

    blt $t6,5,endCheck2
    addi $t2,$t2,1
    li $t6,0

endCheck2: 
    


    j while         #  }

    lw  $ra,0($sp)
    addiu $sp,$sp,4
    li $v0,0
    jr $ra#  return 0;
# } 


# delay function
delay:
    li $v0,12
    syscall     #  resetCoreTimer();
    
    mul $a0,$a0,20000
WhDl:     
    li $v0,11
    syscall             
    blt $v0,$a0,WhDl
    jr $ra

# change line
chln: 
    li $a0,':'
    li $v0,3
    syscall
    jr $ra