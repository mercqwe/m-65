# M-65 Bellek Dökümü

M-65, varsayılan olarak **16 byte**'lık doğrusal bir bellek alanıyla çalışır.
Adresler `0x0`'dan `0xF`'e kadar uzanır — toplamda 16 adet, her biri 8 bitlik hücreden oluşur.

---

## Bellek Haritası

```
+------+----------+---------+----------------------------------+
| ADDR |  İKİLİK  |   HEX   | AÇIKLAMA                         |
+------+----------+---------+----------------------------------+
| 0x0  | 00000000 |  0x00   | Program başlangıcı (genellikle)  |
| 0x1  | 00000000 |  0x00   | Operand / Veri alanı             |
| 0x2  | 00000000 |  0x00   | ...                              |
| 0x3  | 00000000 |  0x00   | ...                              |
| 0x4  | 00000000 |  0x00   | ...                              |
| 0x5  | 00000000 |  0x00   | Veri alanı (sabit değerler)      |
| 0x6  | 00000000 |  0x00   | ...                              |
| 0x7  | 00000000 |  0x00   | ...                              |
| 0x8  | 00000000 |  0x00   | ...                              |
| 0x9  | 00000000 |  0x00   | ...                              |
| 0xA  | 00000000 |  0x00   | ...                              |
| 0xB  | 00000000 |  0x00   | ...                              |
| 0xC  | 00000000 |  0x00   | ...                              |
| 0xD  | 00000000 |  0x00   | ...                              |
| 0xE  | 00000000 |  0x00   | ...                              |
| 0xF  | 00000000 |  0x00   | Son adres                        |
+------+----------+---------+----------------------------------+
```

> **Not:** M-65'te kod ile veri aynı bellek alanını paylaşır.
> Bu mimari yaklaşım **Von Neumann** mimarisi olarak bilinir.
> Kodun nerede bitip verinin nerede başladığını programcı belirler.

---

## Adres Gösterimi

M-65 assembly'sinde adresler **hexadecimal** olarak yazılır.
Aynı adres üç farklı biçimde ifade edilebilir:

| Gösterim     | Örnek      | Açıklama                        |
|:-------------|:-----------|:--------------------------------|
| Hexadecimal  | `0x5`      | Tercih edilen yazım             |
| Onluk        | `5`        | Okunabilirlik için kullanılabilir |
| İkili        | `00000101` | Makine seviyesi, debug için     |

---

## Bellek Yerleşim Örneği


```
ADDR  | İÇERİK | ANLAM
------+--------+-----------------------------
0x0   |  0x01  | OPCODE: LOAD A, <operand>
0x1   |  0x05  | OPERAND: A = 5
0x2   |  0x03  | OPCODE: ADD A, [addr]
0x3   |  0x05  | OPERAND: Adres 0x5'teki değeri topla
0x4   |  0x00  | OPCODE: HALT
0x5   |  0x03  | VERİ: 3 (toplanacak sayı)
0x6   |  0x00  | (boş)
...   |  ...   | ...
0xF   |  0x00  | (boş)
```

Bu programın çalışması sonucunda:
- `A = 5` yüklenir
- `A = A + memory[0x5]` → `A = 5 + 3 = 8`
- Program durur, `Accumulator: 0x08`

---

## M-65 Assembly Sözdizimi

### Genel Bir Assembly Dilinde (x86 tarzı):

```asm
    MOV AX, 5       ; AX registerına 5 yükle
    ADD AX, [0x05]  ; AX'e bellekteki 0x05 adresindeki değeri ekle
    HLT             ; Dur
```

### M-65 Assembly'sinde (tahmini sözdizimi):

```asm
; M-65 Assembly - Örnek Program
; ------------------------------
; A registerına 5 yükle, bellekteki 3 ile topla, dur.

    LOAD  0x05      ; A = 5  (immediate: 0x1 adresindeki değer)
    ADD   0x05      ; A = A + memory[0x05]
    HALT            ; Dur
```

> M-65'te her komut ya **tek başına** (ör. `HALT`) ya da **bir operandla** (ör. `LOAD 0x05`) yazılır.

---

## Komut → Makine Kodu Dönüşümü

```
Assembly        →   Makine Kodu (Hex)   →   Belleğe Yazılış
-------------       ------------------      ------------------
LOAD  0x05      →   01 05               →   memory[0]=0x01, memory[1]=0x05
ADD   0x05      →   03 05               →   memory[2]=0x03, memory[3]=0x05
HALT            →   00                  →   memory[4]=0x00
[veri: 3]       →   03                  →   memory[5]=0x03
```

---

## İleride Eklenebilecek Komutlar (Tahmini)

Projeyi genişletmek istersen şu komutlar mantıklı birer adım olur:

| Opcode | Komut  | Açıklama                                         |
|:-------|:-------|:-------------------------------------------------|
| 0x05   | SUB    | A'dan bellek değerini çıkar                      |
| 0x06   | JZ     | Eğer A sıfırsa hedef adrese zıpla (F flag'ı kullanır) |
| 0x07   | JNZ    | Eğer A sıfır değilse zıpla                       |
| 0x08   | INC    | A'yı 1 artır                                     |
| 0x09   | DEC    | A'yı 1 azalt                                     |
| 0x0A   | OUT    | A'nın değerini ekrana bas                        |

Bu komutlarla bir `for` döngüsü bile yazılabilir hale gelir.

---

*M-65 — Hobi amaçlı 8-bit işlemci emülatörü*
