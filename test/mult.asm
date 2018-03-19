// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// R2=0
// while(R1 != 0)
//   R2=R2+R0
//   R1=R1-1



@R2
M=0

@3
D=A

@R0
M=D // R0=3

@2
D=A

@R1
M=D // R1=2
(LOOP)
  @R1
  D=M
  @END
  D;JEQ   // if(R1==0) goto END
  
  @R0
  D=M       // D = R0
  @R2
  M=D+M    // R2 = R2+ R0
  
  @R1
  M=M-1     // R1--
  
  @LOOP
  0;JMP     // goto LOOP

(END)

  @R2
  D=M
