#include "cpu.h"
#include <stdio.h>

/*
  ÖRNEK PROGRAM: 1'den 4'e kadar say, toplamı bul, 10'dan büyükse HALT, değilse
  geri say

  BELLEK HARITASI:
  +------+-------+--------------------------------+
  | ADDR | DEGER | ACIKLAMA                       |
  +------+-------+--------------------------------+
  | 0x0  | 0x01  | LOAD #1                        |
  | 0x1  | 0x01  |                                |
  | 0x2  | 0x05  | ADD #sayac (döngü başı)         |
  | 0x3  | 0x01  |                                |
  | 0x4  | 0x02  | STORE toplam adresine          |
  | 0x5  | 0x0E  |                                |
  | 0x6  | 0x07  | SUB #10                        |
  | 0x7  | 0x0A  |                                |
  | 0x8  | 0x09  | JZ -> HALT (toplam == 10 ise)  |
  | 0x9  | 0x0D  |                                |
  | 0xA  | 0x08  | LOAD ind toplam                |
  | 0xB  | 0x0E  |                                |
  | 0xC  | 0x04  | JMP -> 0x2 (döngü devam)       |
  | 0xD  | 0x02  |                                |
  | 0xE  | 0x00  | VERI: toplam alanı             |
  | 0xF  | 0x00  | HALT                           |
  +------+-------+--------------------------------+
*/

int main() {
  init_cpu();
  printf("M-65 baslatildi\n");
  printf("Program: toplam 10 olana kadar 1'er 1'er say\n\n");

  // --- KOD BOLUMU ---
  memory[0x0] = 0x01; // LOAD #1
  memory[0x1] = 0x01; // A = 1 (baslangic degeri)

  memory[0x2] = 0x05; // ADD #1  ← döngü başı (her turda 1 ekle)
  memory[0x3] = 0x01;

  memory[0x4] = 0x02; // STORE toplam adresine
  memory[0x5] = 0x0E; // memory[0xE] = A

  memory[0x6] = 0x07; // SUB #10 (A - 10, sıfır oldu mu?)
  memory[0x7] = 0x0A;

  memory[0x8] = 0x09; // JZ → 0xF (A == 0 yani toplam 10'du, bitir)
  memory[0x9] = 0x0F;

  memory[0xA] = 0x08; // LOAD ind (toplami geri yükle, SUB bozmadan devam)
  memory[0xB] = 0x0E;

  memory[0xC] = 0x04; // JMP → 0x2 (döngüye dön)
  memory[0xD] = 0x02;

  // --- VERI BOLUMU ---
  memory[0xE] = 0x00; // toplam alanı (başta boş)
  memory[0xF] = 0x00; // HALT

  fetch_decode_execute();

  printf("\n--- SONUC ---\n");
  printf("Accumulator : %d\n", A);
  printf("memory[0xE] : %d\n", memory[0xE]);
  return 0;
}
