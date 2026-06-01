#include "opcodes.h"
#include <stdio.h>

void op_halt(int *running) {
  printf("HALT: Islemci durduruldu\n");
  *running = 0;
}

void op_load_imm() { // LOAD #n  (immediate)
  A = memory[PC];
  PC++;
  printf("LOAD #%d\n", A);
}

void op_load_ind() { // LOAD addr  (indirect)
  A = memory[memory[PC]];
  PC++;
  printf("LOAD [ind]: A = %d\n", A);
}

void op_store() { // STORE addr
  uint8_t addr = memory[PC];
  memory[addr] = A;
  PC++;
  printf("STORE [0x%02X] = %d\n", addr, A);
}

void op_add_ind() { // ADD addr  (indirect)
  uint8_t val = memory[memory[PC]];
  A += val;
  PC++;
  printf("ADD [ind]: +%d, A = %d\n", val, A);
}

void op_add_imm() { // ADD #n  (immediate)
  uint8_t val = memory[PC];
  A += val;
  PC++;
  printf("ADD #%d, A = %d\n", val, A);
}

void op_jmp() { // JMP addr
  PC = memory[PC];
  printf("JMP -> 0x%02X\n", PC);
}

void op_sub_ind() { // SUB addr  (indirect)
  uint8_t val = memory[memory[PC]];
  A -= val;
  PC++;
  printf("SUB [ind]: -%d, A = %d\n", val, A);
}

void op_sub_imm() { // SUB #n  (immediate)
  uint8_t val = memory[PC];
  A -= val;
  PC++;
  printf("SUB #%d, A = %d\n", val, A);
}

void op_jz() { // JZ addr — A == 0 ise zıpla
  if (A == 0) {
    PC = memory[PC];
    printf("JZ -> zipladi, PC = 0x%02X\n", PC);
  } else {
    PC++; // zıplamıyorsa operandı atla
    printf("JZ -> atlandi (A = %d)\n", A);
  }
}

void op_jnz() { // JNZ addr — A != 0 ise zıpla
  if (A != 0) {
    PC = memory[PC];
    printf("JNZ -> zipladi, PC = 0x%02X\n", PC);
  } else {
    PC++; // zıplamıyorsa operandı atla
    printf("JNZ -> atlandi (A = 0)\n");
  }
}
