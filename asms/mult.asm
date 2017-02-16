// Calculate x * y
@2
@R1    // Load R1 to A
D=M    // D = y
@R3    // Load R3 to A
M=D    // R3 = y, so that data in R1 won't be touched
@R2    // Load R2 to A
M=0    // Reset R2 to 0, so the result from previous time won't interfere

(LOOP)
    @R3    // Load R3 to A
    D=M    // D = y
    @END    // Load END to A
    D;JLE    // if y < 0, goto END
    @R3    // Load R3 back to A
    M=D-1    // if y >= 0, y -= 1
    @R0    // Load R0 to A
    D=M    // D = x
    @R2    // Load R2(result) to A
    M=D+M    // R2 += x
    @LOOP
    0;JMP    // Goto LOOP
(END)
    @END
    0;JMP    // Infinite loop


