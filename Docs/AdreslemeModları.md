# M-65 — Adresleme Modları

## Önce Temel Soru: "Operand Ne Demek?"

Her komut bir şey **yapar**, bazıları da bir şeyle **yapar**.
O "bir şey" — operanddır.

```
LOAD  0x05
^^^^  ^^^^
komut  operand
```

Ama operand her zaman aynı şekilde yorumlanmaz.
**"Bu sayıyı nasıl kullanacaksın?"** sorusunun cevabı → Adresleme Modudur.

---

## M-65'teki Adresleme Modları

### 1. Immediate (Anlık)

> "Operandın kendisi veridir."

```c
case 0x01: {         // LOAD
    A = memory[PC];  // PC'nin gösterdiği byte doğrudan A'ya gider
    PC++;
}
```

```
Bellek:  [0x01] [0x05]
          LOAD    ↓
                  A = 5   ← 0x05'in kendisi
```

Operand olarak ne yazdıysan, A'ya o girer. Başka bir adrese bakılmaz.

**Gerçek hayat analojisi:**
"Şu an elindeki parayı ver" — cebine bakılmaz, elde ne varsa o kullanılır.

---

### 2. Indirect (Dolaylı)

> "Operand bir adrestir. Asıl veri o adresin içindedir."

```c
case 0x03: {                        // ADD
    uint8_t val = memory[memory[PC]]; // önce adresi oku, sonra o adrese git
    A += val;
    PC++;
}
```

```
Bellek:  [0x03] [0x0C] ... [0x02]
          ADD     ↓              ↑
               adres = 0xC ——→  memory[0xC] = 2
                                A += 2
```

İki adım var:
1. Operandı oku → bu bir adres numarası
2. O adrese git → oradaki değeri kullan

**Gerçek hayat analojisi:**
"Cüzdanındaki para kadar ver" — önce cüzdana bak, sonra içindeki miktarı al.

---

### Karşılaştırma

```
Mod        | Operand ne yapar?          | Kaç bellek erişimi?
-----------+----------------------------+--------------------
Immediate  | Kendisi veridir            | 1 (direkt)
Indirect   | Başka bir adrese işaret    | 2 (adres → değer)
```

---

### M-65'te Hangi Komut Hangi Modu Kullanıyor?

```
Komut  | Mod       | Ne yapar?
-------+-----------+------------------------------------------
LOAD   | Immediate | A = operandın kendisi
ADD    | Indirect  | A += memory[operand]
STORE  | Indirect  | memory[operand] = A
JMP    | Indirect  | PC = memory[PC]  (adrese zıplar)
HALT   | —         | Operand yok
```

> **Dikkat:** M-65'te LOAD ve ADD farklı modlar kullanıyor.
> Bu bir tutarsızlık — ilerleyen sürümlerde `LOAD [addr]` ekleyince netleşecek.

---

## Diğer Adresleme Modları (6502'de Var, M-65'te Henüz Yok)

Bunları şimdi ekleme, ama ne olduklarını bilmek ISA'nı genişletirken yol gösterir.

---

### 3. Direct / Absolute (Doğrudan)

> "Operand bir adrestir, o adresteki değeri kullan."
> Indirect ile aynı görünür ama tek katlıdır — adres doğrudan bellekte aranır.

```asm
LOAD [0x05]   ; A = memory[0x05]
```

```
Bellek:  [0x01] [0x05] ... [0x09]
          LOAD    ↓              ↑
               adres = 0x5 ——→  memory[0x5] = 9
                                A = 9
```

6502'de buna **Zero Page** adresleme de denir — ilk 256 byte'a tek byte'lık adresle erişim.

---

### 4. Register (Yazmaç)

> "Operand bir register'dır, bellekle işi yok."

```asm
ADD A, B   ; A = A + B  (iki register toplanır)
```

M-65'in şu an sadece bir register'ı var (`A`), bu yüzden bu mod anlamsız.
İkinci bir register (`B` veya `X`) eklenince kullanılabilir hale gelir.

---

### 5. Indexed (İndeksli)

> "Bir taban adres + bir register = asıl adres."

```asm
LOAD A, [0x05 + X]   ; A = memory[0x05 + X]
```

6502'de `X` ve `Y` register'ları tam bu iş için vardır.
Diziler üzerinde döngü kurmayı sağlar:

```
X = 0 → memory[0x05 + 0] = memory[0x05]   ← 1. eleman
X = 1 → memory[0x05 + 1] = memory[0x06]   ← 2. eleman
X = 2 → memory[0x05 + 2] = memory[0x07]   ← 3. eleman
```

M-65'e ikinci bir register ve indexed mod eklenirse gerçek dizi işlemleri mümkün olur.

---

### 6. Implied / Inherent (Örtük)

> "Komutun operanda ihtiyacı yok, ne yapacağı zaten bellidir."

```asm
HALT   ; operand yok, dur
```

M-65'te `HALT` zaten bu moddadır. İleride eklenebilecek `INC A`, `DEC A` gibi komutlar da bu kategoriye girer.

---

## Özet Tablosu

```
Mod        | Örnek          | A'ya ne gider?              | 6502'de var mı?
-----------+----------------+-----------------------------+----------------
Immediate  | LOAD #5        | 5 (operandın kendisi)       | Evet
Direct     | LOAD [0x05]    | memory[0x05]                | Evet (Zero Page)
Indirect   | ADD [0x05]     | memory[memory[0x05]]        | Evet
Indexed    | LOAD [0x05+X]  | memory[0x05 + X]            | Evet
Register   | ADD A, B       | A + B                       | Kısmi
Implied    | HALT           | —                           | Evet
```

---

## M-65 İçin Öneri

Şu an LOAD immediate, ADD indirect çalışıyor.
Mantıklı bir sonraki adım:

```
0x01  LOAD #imm      → Immediate   (zaten var)
0x05  LOAD [addr]    → Direct      (eklenebilir)
0x03  ADD [addr]     → Indirect    (zaten var)
0x08  INC            → Implied     (kolay eklenir)
```

`LOAD [addr]` eklenince kod ve veriyi daha net ayırabilirsin
— immediate ile sabit değer, direct ile bellekteki değişken veri yüklersin.

---

*M-65 — Hobi amaçlı 8-bit işlemci emülatörü*
