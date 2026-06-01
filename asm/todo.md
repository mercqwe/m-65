# M-65 — Assembler Yol Haritası

Şu an programlar doğrudan `main.c` içine hardcode ediliyor.
Hedef: `.m65` uzantılı bir assembly dosyası yazıp bunu otomatik olarak makine koduna çevirmek.

---

## Neden Assembler?

Şu an bir program yazmak için şunu yapıyoruz:

```c
memory[0x0] = 0x01; // LOAD #1
memory[0x1] = 0x01;
memory[0x2] = 0x05; // ADD #1
memory[0x3] = 0x01;
```

Assembler olunca şunu yazacağız:

```asm
LOAD #1
ADD  #1
```

Assembler bu dosyayı okuyup yukarıdaki C kodunu otomatik üretecek.

---

## Dosya Yapısı (Hedef)

```
M-65/
├── src/              ← emülatör
├── Docs/             ← dökümanlar
├── asm/              ← assembler
│   ├── assembler.c   ← .m65 dosyasını okur, makine koduna çevirir
│   └── programs/     ← yazılacak assembly programları
│       └── ornek.m65
└── bin/
    ├── mirac65       ← emülatör binary
    └── m65asm        ← assembler binary (ileride)
```

---

## .m65 Sözdizimi

Uzantı `.m65` — özgün, M-65'e özel.

```asm
; bu bir yorum satırı
LOAD #1       ; immediate: A = 1
ADD  #1       ; immediate: A += 1
STORE 0x0E    ; indirect:  memory[0xE] = A
SUB  #10      ; immediate: A -= 10
JZ   0x0F     ; A == 0 ise 0xF'e zıpla
LOAD 0x0E     ; indirect:  A = memory[0xE]
JMP  0x02     ; 0x2'ye dön
HALT
```

**Kurallar:**
- `;` ile başlayan satırlar yorum, atlanır
- `#` varsa → immediate mod
- `#` yoksa → indirect mod
- Adresler hex (`0x0E`) veya decimal (`14`) yazılabilir
- Büyük/küçük harf fark etmez (`LOAD` = `load`)

---

## Assembler Nasıl Çalışacak?

Tek görevi şu: `.m65` dosyasını satır satır okuyup `memory[]` dizisini doldurmak.

```
Adım 1 — Oku
  "LOAD #1"  →  token[0] = "LOAD", token[1] = "#1"

Adım 2 — Parse et
  "LOAD" + "#" var  →  immediate mod  →  opcode = 0x01
  operand = 1

Adım 3 — Belleğe yaz
  memory[PC++] = 0x01
  memory[PC++] = 0x01

Adım 4 — Sonraki satır
```

---

## Adresleme Modu Tespiti

Assembler `#` varlığına göre opcode seçer:

| Yazılan | # var mı? | Seçilen Opcode |
| :--- | :--- | :--- |
| `LOAD #5` | Evet | `0x01` (immediate) |
| `LOAD 0x0C` | Hayır | `0x08` (indirect) |
| `ADD #3` | Evet | `0x05` (immediate) |
| `ADD 0x0C` | Hayır | `0x03` (indirect) |
| `SUB #1` | Evet | `0x07` (immediate) |
| `SUB 0x0C` | Hayır | `0x06` (indirect) |
| `JMP 0x02` | — | `0x04` |
| `JZ  0x0F` | — | `0x09` |
| `JNZ 0x02` | — | `0x0A` |
| `STORE 0x0E` | — | `0x02` |
| `HALT` | — | `0x00` |

---

## Kullanım (Hedef)

```bash
# Assembly dosyasını derle ve çalıştır
./bin/m65asm asm/programs/ornek.m65

# İleride: sadece makine kodu üret, çalıştırma
./bin/m65asm asm/programs/ornek.m65 --compile-only
```

---

## Geliştirme Aşamaları

- [ ] `assembler.c` temel parser — satır okuma, token ayırma
- [ ] Opcode tablosu — komut adı + mod → opcode eşleştirmesi
- [ ] `memory[]` yükleme ve emülatörü çalıştırma
- [ ] Yorum satırı desteği (`;`)
- [ ] Hata mesajları — bilinmeyen komut, adres taşması
- [ ] İleride: label desteği (`dongu:`, `JNZ dongu`)

---

## Label (İleride)

Şu an adresler elle yazılıyor:

```asm
JNZ 0x02   ; 0x2 döngü başı
```

Label eklenince:

```asm
dongu:
  ADD  #1
  SUB  #10
  JNZ  dongu   ; assembler 0x2'yi otomatik hesaplar
HALT
```

Bu assembler'ın iki geçişli (`two-pass`) çalışmasını gerektirir:
1. Geçiş: label adreslerini topla
2. Geçiş: opcode üret, label'ları adresle değiştir

---

*M-65 — Hobi amaçlı 8-bit işlemci emülatörü*
