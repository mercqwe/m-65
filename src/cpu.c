#include "cpu.h"
#include "opcodes.h"
#include <stdint.h>
#include <stdio.h>

uint8_t memory[16];
uint8_t A;
uint8_t PC;
uint8_t F;

void init_cpu() {
  A = 0;
  PC = 0;
  F = 0;
  for (int i = 0; i < 16; i++)
    memory[i] = 0;
}

void fetch_decode_execute() {
  int running = 1;
  while (running) {
    uint8_t opcode = memory[PC];
    PC++;
    switch (opcode) {
    case 0x00:
      op_halt(&running);
      break;
    case 0x01:
      op_load_imm();
      break;
    case 0x02:
      op_store();
      break;
    case 0x03:
      op_add_ind();
      break;
    case 0x04:
      op_jmp();
      break;
    case 0x05:
      op_add_imm();
      break;
    case 0x06:
      op_sub_ind();
      break;
    case 0x07:
      op_sub_imm();
      break;
    case 0x08:
      op_load_ind();
      break;
    case 0x09:
      op_jz();
      break;
    case 0x0A:
      op_jnz();
      break;
    default:
      printf("Bilinmeyen komut: 0x%02X\n", opcode);
      break;
    }
  }
}
