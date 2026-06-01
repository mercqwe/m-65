# M-65 — Komut Seti (ISA)

M-65 işlemcisi 8-bitlik opcode değerleri kullanır.
Adresleme modu belirtilmemişse komut **indirect** çalışır.
`#` sembolü **immediate** modu ifade eder.

---

## Mevcut Komutlar

| Opcode | Komut | Mod | Sözdizimi | Açıklama |
| :--- | :--- | :--- | :--- | :--- |
| `0x00` | HALT | Implied | `HALT` | İşlem döngüsünü durdurur. |
| `0x01` | LOAD | Immediate | `LOAD #n` | A = n |
| `0x02` | STORE | Indirect | `STORE addr` | memory[addr] = A |
| `0x03` | ADD | Indirect | `ADD addr` | A += memory[addr] |
| `0x04` | JMP | Indirect | `JMP addr` | PC = addr |
| `0x05` | ADD | Immediate | `ADD #n` | A += n |
| `0x06` | SUB | Indirect | `SUB addr` | A -= memory[addr] |
| `0x07` | SUB | Immediate | `SUB #n` | A -= n |
| `0x08` | LOAD | Indirect | `LOAD addr` | A = memory[addr] |
| `0x09` | JZ | Implied | `JZ addr` | A == 0 ise PC = addr, değilse devam et |
| `0x0A` | JNZ | Implied | `JNZ addr` | A != 0 ise PC = addr, değilse devam et |

---

## Planlanan Komutlar

### İkincil — İşleri kolaylaştırır

| Tahmini Opcode | Komut | Mod | Sözdizimi | Açıklama | Neden Lazım? |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `0x0B` | INC | Implied | `INC` | A += 1 | `ADD #1` kısayolu, döngü sayacı için |
| `0x0C` | DEC | Implied | `DEC` | A -= 1 | `SUB #1` kısayolu, geri sayım için |
| `0x0D` | CMP | Immediate | `CMP #n` | A - n sonucunu F'e yaz, A değişmez | Karşılaştırma — A'yı bozmadan |
| `0x0E` | OUT | Implied | `OUT` | A'yı ekrana yaz | Debug ve çıktı için |

### İleride — Mimariyi güçlendirir

| Tahmini Opcode | Komut | Mod | Sözdizimi | Açıklama | Neden Lazım? |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `0x0F` | AND | Immediate | `AND #n` | A = A & n | Bit maskeleme, flag kontrolü |
| — | OR | Immediate | `OR #n` | A = A \| n | Bit set etme |
| — | XOR | Immediate | `XOR #n` | A = A ^ n | Bit toggle, basit şifreleme |
| — | SHL | Implied | `SHL` | A = A << 1 | A'yı 2 ile çarp |
| — | SHR | Implied | `SHR` | A = A >> 1 | A'yı 2'ye böl |

---

## F Register ve Flag'ler (Planlanıyor)

Şu an `F` tanımlı ama kullanılmıyor.
`CMP` eklenince ve `JZ`/`JNZ` flag'e bağlanınca anlam kazanacak.

| Bit | Flag | Ne zaman set olur? |
| :--- | :--- | :--- |
| 0 | **Z** (Zero) | A == 0 olduğunda |
| 1 | **C** (Carry) | Toplama taşma yaptığında |
| 2 | **N** (Negative) | A'nın en yüksek biti 1 olduğunda |

> **Not:** Şu an `JZ` ve `JNZ` doğrudan A'ya bakıyor.
> Flag'ler eklenince bu komutlar F register'ındaki Z bitini okuyacak şekilde güncellenecek.

---

## Örnek: JNZ ile Geri Sayım Döngüsü

```asm
; 3'ten 0'a geri say
LOAD #3       ; 0x0: A = 3
SUB  #1       ; 0x2: A -= 1   ← döngü başı
JNZ  0x02     ; 0x4: A != 0 ise 0x2'ye dön
HALT          ; 0x6: dur
```

Makine kodu karşılığı:

```
memory[0x0] = 0x01;  // LOAD #3
memory[0x1] = 0x03;
memory[0x2] = 0x07;  // SUB #1
memory[0x3] = 0x01;
memory[0x4] = 0x0A;  // JNZ
memory[0x5] = 0x02;  // hedef adres
memory[0x6] = 0x00;  // HALT
```

---

*M-65 — Hobi amaçlı 8-bit işlemci emülatörü*
