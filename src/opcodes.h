#ifndef OPCODES_H
#define OPCODES_H

#include "cpu.h"

void op_halt(int *running);
void op_load_imm();
void op_load_ind();
void op_store();
void op_add_ind();
void op_add_imm();
void op_jmp();
void op_sub_ind();
void op_sub_imm();
void op_jz();
void op_jnz();

#endif
