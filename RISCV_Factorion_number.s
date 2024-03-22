.text
    .globl _start

# storing given number in x12 initially
# copying given number in x15 for comparison later
# storing sum of factorials of digits in x11, initialised as 0
# storing 10 in x17 for obtaining one's digit 

_start:
    li x12, 40585
    mv x15,x12
    li x11, 0
    li x17, 10
    j loop

#storing one's digit in x13 using a loop
#removing the one's digit from x12
#thus this code works for n-digit number (eg., 40585)
#storing 1 in x14 for factorial and jumping to factorial

loop:
    
    rem x13, x12,x17
    div x12, x12, x17
        
    li x14, 1
    j factorial
    
#jumping back to the next statement in loop after factorial has been calculated for one's digit
#adding factorial to sum variable, i.e., x11
#jumping back to beginning of loop 

next:
    add x11, x11, x14
    
    beq x12, x0, check

    j loop
    
factorial:    
# simple factorial calculation 
    addi x16, x0, 1
    ble x13, x16, next
    mul x14, x13, x14
    addi x13, x13, -1
    j factorial 

check:
#comparing x11 (sum of factorials number) and x17 (copied original number)
    beq x15,x11,correct
    j incorrect
    
# storing 1( is a Factorion number) or 0 (isn't) in x10 (overwriting x10)
incorrect:
    li x10,0
    j exit 
correct:
    li x10,1
    j exit
exit:
    add x0,x0,x0

# finally the input is in x15, sum of factorials in x11 and, answer is in x10