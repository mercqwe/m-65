# M-65 — Control Unit ve Program Counter

## Control Unit Nedir?

İşlemcinin içinde iki ana kısım vardır:

- **ALU (Arithmetic Logic Unit):** Matematiği yapan kısım. Toplar, çıkarır.
- **Control Unit (CU):** Neyin ne zaman yapılacağına karar veren kısım. Trafik polisi gibi.

M-65'te `fetch_decode_execute()` fonksiyonu **Control Unit'in ta kendisidir.**
Bu fonksiyon her döngüde şu üç soruyu sorar:

> "Şu an hangi komutu çalıştırmalıyım? Ne demek istiyor? Hemen yap."

---

## Program Counter (PC) Nedir?

PC, bellekte **"şu an neredeyim?"** sorusunun cevabıdır.

Bir kitap okurken parmağını sayfada gezdirdiğini düşün.
PC de tam olarak o parmaktır — hangi byte'ı okumam gerekiyor diye işaret eder.

```c
uint8_t PC;  // Sadece bir sayı. 0'dan 15'e kadar gidebilir (16 byte bellek).
```

Başlangıçta `PC = 0`'dır. İlk komutu `0x0` adresinden okur.

---

## PC Döngü İçinde Nasıl İlerler?

```c
while (running) {
    uint8_t opcode = memory[PC];   // 1. PC'nin gösterdiği adresi oku
    PC++;                          // 2. PC'yi bir ilerlet
    switch (opcode) { ... }        // 3. Komutu çalıştır
}
```

Her döngüde **en az bir kez** `PC++` çalışır.
Eğer komutun bir de operandı varsa (ek veri), `PC++` bir kez daha çalışır.

---

## Adım Adım: Bellekteki Program


```
ADDR  | DEĞER | ANLAM
------+-------+---------------------------
0x0   | 0x01  | LOAD komutu
0x1   | 0x01  | LOAD'un operandı → A = 1
0x2   | 0x03  | ADD komutu
0x3   | 0x0C  | ADD'in operandı → adres 0xC'yi kullan
...
0xA   | 0x00  | HALT
0xC   | 0x02  | Veri: 2
```

Şimdi PC'nin bu belleğin içinde nasıl gezdiğini takip edelim:

---

### Döngü 1 — LOAD komutu okunuyor

```
Bellek: [0x01] [0x01] [0x03] [0x0C] ... [0x00] ...
          ↑
          PC = 0x0
```

```c
uint8_t opcode = memory[PC];   // memory[0x0] = 0x01  → opcode = LOAD
PC++;                          // PC artık 0x1
```

`switch` içinde `case 0x01` çalışır:

```c
case 0x01: {
    A = memory[PC];   // memory[0x1] = 0x01  → A = 1
    PC++;             // PC artık 0x2
}
```

```
Bellek: [0x01] [0x01] [0x03] [0x0C] ...
                         ↑
                         PC = 0x2
```

> **PC şu an 0x2'de.** LOAD 2 byte tüketti: 1 opcode + 1 operand.

---

### Döngü 2 — ADD komutu okunuyor

```
Bellek: [0x01] [0x01] [0x03] [0x0C] ...
                         ↑
                         PC = 0x2
```

```c
uint8_t opcode = memory[PC];   // memory[0x2] = 0x03  → opcode = ADD
PC++;                          // PC artık 0x3
```

`switch` içinde `case 0x03` çalışır:

```c
case 0x03: {
    uint8_t val = memory[memory[PC]];
    //                    memory[0x3] = 0x0C   → önce operandı oku: adres = 0xC
    //            memory[0x0C] = 0x02           → o adresteki değer = 2
    A += val;    // A = 1 + 2 = 3
    PC++;        // PC artık 0x4
}
```

> **ADD çift katlı okuma yapar:**
> 1. `memory[PC]` → operand (bir adres numarası)
> 2. `memory[o adres]` → asıl veri

---

### HALT — PC'nin sonu

Bir noktada PC `0xA`'ya gelir:

```c
uint8_t opcode = memory[PC];   // memory[0xA] = 0x00  → opcode = HALT
PC++;                          // PC artık 0xB (ama artık kullanılmayacak)
```

```c
case 0x00: {
    running = 0;   // Döngü durur, PC bir daha okunmaz
}
```

---

## PC Özeti — Tek Bakışta

```
KOMUT     | PC başta | PC sonda | Kaç byte tüketti?
----------+----------+----------+------------------
LOAD      |   0x0    |   0x2    | 2  (opcode + operand)
ADD       |   0x2    |   0x4    | 2  (opcode + operand)
STORE     |   0x?    |   0x?+2  | 2  (opcode + operand)
HALT      |   0xA    |   0xB*   | 1  (sadece opcode)
JMP       |   0x?    |  hedef   | PC doğrudan değişir
```

`*` HALT sonrası PC ilerler ama döngü durduğu için önemi yoktur.

---

## JMP — PC'yi Zorla Değiştirmek

Diğer komutlar PC'yi sırayla ilerletir.
**JMP ise PC'yi istediğin bir adrese fırlatır.**

```c
case 0x04: {
    PC = memory[PC];   // Operand ne diyorsa, PC oraya zıplar
}
```

Eğer `memory[PC] = 0x2` ise, program `0x2` adresine döner ve oradan devam eder.
Dikkat: `PC++` **yoktur** burada — PC zaten değişti.

Bu sayede döngü yazılabilir:

```
0x0: LOAD  → A = 0
0x2: ADD   → A += 1
0x4: JMP   → 0x2'ye dön  ← sonsuz döngü!
```

> JMP + koşullu zıplama (`JZ`, `JNZ`) eklenince gerçek `for` döngüleri mümkün olur.

---

## Özet

| Kavram | M-65'teki karşılığı |
|:-------|:--------------------|
| Control Unit | `fetch_decode_execute()` fonksiyonunun tamamı |
| Program Counter | `uint8_t PC` değişkeni |
| Fetch | `memory[PC]` okuma satırı |
| Decode | `switch(opcode)` bloğu |
| Execute | Her `case` içindeki işlemler |
| PC ilerlemesi | `PC++` satırları |
| Dallanma | `PC = memory[PC]` (JMP) |

---

*M-65 — Hobi amaçlı 8-bit işlemci emülatörü*
