.data

.text
.globl main

main:           # int main(void)
                # {
    li $t0,0    #  int counter = 0;
while:          #  while(1)
                #  {
    li $a0,'\r'
    li $v0,3    
    syscall     #  putChar('\r'); // cursor regressa ao inicio da linha no ecrã

    li $a1,0x0004000A
    move $a0,$t0
    li $v0, 6   
    syscall     #  printInt(counter, 10 | 4 << 16); // Ver nota de rodapé 1
    
    li $v0,12
    syscall     #  resetCoreTimer();
Wh2:  
    li $v0,11
    syscall             
    blt $v0,20000000,Wh2 #  while(readCoreTimer() < 200000);

    addi $t0,$t0,1     #  counter++;

    j while         #  }

    li $v0,0
    jr $ra#  return 0;
# } 