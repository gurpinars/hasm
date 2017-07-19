#ifndef HVM_HVM_H
#define HVM_HVM_H

#include <stdio.h>
#include <stdint.h>

#define ROM_SIZE 32768 /* 32KB */
#define RAM_SIZE 16384 /* 16KB */

enum opcodes {
    COMP_ZERO = 0x3AA,
    COMP_ONE = 0x3BF,
    COMP_MINUS_1 = 0x3BA,
    COMP_D = 0x38C,
    COMP_A = 0x3B0,
    COMP_NOT_D = 0x38D,
    COMP_NOT_A = 0x3B1,
    COMP_MINUS_D = 0x38F,
    COMP_MINUS_A = 0x3B3,
    COMP_D_PLUS_1 = 0x39F,
    COMP_A_PLUS_1 = 0x3B7,
    COMP_D_MINUS_1 = 0x38E,
    COMP_A_MINUS_1 = 0x3B2,
    COMP_D_PLUS_A = 0x382,
    COMP_D_MINUS_A = 0x393,
    COMP_A_MINUS_D = 0x387,
    COMP_D_AND_A = 0x380,
    COMP_D_OR_A = 0x395,
    COMP_M = 0x3F0,
    COMP_NOT_M = 0x3F1,
    COMP_MINUS_M = 0x3F3,
    COMP_M_PLUS_1 = 0x3F7,
    COMP_D_PLUS_M = 0x3C2,
    COMP_D_MINUS_M = 0x3D3,
    COMP_M_MINUS_D = 0x3C7,
    COMP_D_AND_M = 0x3C0,
    COMP_D_OR_M = 0x3D5,
    DEST_M = 0x1,
    DEST_D = 0x2,
    DEST_MD = 0x3,
    DEST_A = 0x4,
    DEST_AM = 0x5,
    DEST_AD = 0x6,
    DEST_AMD = 0x7,
    JGT = 0x1,
    JEQ = 0x2,
    JGE = 0x3,
    JLT = 0x4,
    JNE = 0x5,
    JLE = 0x6,
    JMP = 0x7,
};

struct HVMData_ {
    uint16_t comp:10;
    uint8_t dest:3;
    uint8_t jmp:3;
    int16_t A_REG:16;
    int16_t D_REG:16;
    int ex_state;
    int pc;
};
typedef struct HVMData_ HVMData;

/* Memory */
uint16_t ROM[ROM_SIZE];
int16_t RAM[RAM_SIZE];

/* vm init */
void vm_init(char *arg);

/* Instruction cycle: Fetch, Decode, Execute */
uint16_t fetch(HVMData *hdt);
void decode(uint16_t instr, HVMData *hdt);
void execute(HVMData *hdt);

/* Memory snapshot */
void snapshot(HVMData *hdt);
#endif //HVM_HVM_H
