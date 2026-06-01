#ifndef CPU_H
#define CPU_H

#include <stdint.h> // 8 bit veri icin

// Memory
extern uint8_t memory[16];

// Registerlar
extern uint8_t A;
extern uint8_t PC;
extern uint8_t F;

// Fonksiyonlar (umarım)
void init_cpu();
void fetch_decode_execute();

#endif
