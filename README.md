# M-65 — 8-Bit Custom CPU Emulator

> **Bu bir hobi öğrenme projesidir.** İşlemci mimarisini, fetch-decode-execute döngüsünü ve bellek yönetimini sıfırdan öğrenmek amacıyla yazılmıştır.

---

## Hakkında

M-65, tamamen özgün bir mimari üzerine yazılmış 8-bitlik bir işlemci emülatörüdür.
6502 mimarisinden ilham alınmış, Von Neumann bellek modeli kullanılmaktadır.

## Mimari Özellikleri

| Özellik | Değer |
| :--- | :--- |
| Bellek | 16 Byte (0x0 — 0xF) |
| Bellek Modeli | Von Neumann (kod ve veri aynı alanda) |
| Veri Genişliği | 8-bit |

**Registerlar:**

| Register | İsim | Açıklama |
| :--- | :--- | :--- |
| `A` | Accumulator | Tüm aritmetik işlemler buradan geçer |
| `PC` | Program Counter | Sıradaki komutun adresini tutar |
| `F` | Status Flags | Zero, Carry, Negative bitleri (planlanıyor) |

---

## Kurulum ve Çalıştırma

```bash
git clone https://github.com/merc/m-65.git
cd m-65
make
./bin/m65
```

---

## Dosya Yapısı

```
M-65/
├── README.md
├── Makefile
├── src/
│   ├── main.c        # Programın giriş noktası, bellek yükleme
│   ├── cpu.c         # FDE döngüsü ve register tanımları
│   ├── cpu.h         # Extern tanımlar ve fonksiyon prototipleri
│   ├── opcodes.c     # Her komutun implementasyonu
│   └── opcodes.h     # Opcode fonksiyon prototipleri
├── Docs/
│   ├── ISA.md
│   ├── FDE.md
│   ├── PCveControlUnit.md
│   ├── AdreslemeModları.md
│   └── Memory Dump.md
└── bin/
    └── m65
```

---

## Dokümantasyon

| Döküman | Açıklama |
| :--- | :--- |
| [ISA.md](Docs/ISA.md) | Komut seti, opcode tablosu, planlanan komutlar |
| [FDE.md](Docs/FDE.md) | Fetch-Decode-Execute döngüsü nasıl çalışır |
| [PCveControlUnit.md](Docs/PCveControlUnit.md) | Program Counter ve Control Unit detayları |
| [AdreslemeModları.md](Docs/AdreslemeModları.md) | Immediate, Indirect ve diğer adresleme modları |
| [Memory Dump.md](Docs/Memory%20Dump.md) | Bellek haritası ve assembly sözdizimi |

---

## Roadmap

- [x] Dosya yapısı oluşturuldu
- [x] FDE döngüsü öğrenildi ve implemente edildi
- [x] Bellek dizisi tanımlandı (16 byte, Von Neumann)
- [x] Opcode sistemi kuruldu, opcodes.c ayrıştırıldı
- [x] Temel komutlar: LOAD, STORE, ADD, SUB, JMP, JZ, JNZ
- [ ] Assembler yazılacak (`#` ile immediate, `[addr]` ile indirect)
- [ ] F register aktif edilecek (Zero, Carry, Negative flag'leri)
- [ ] INC, DEC, CMP, OUT komutları eklenecek
- [ ] Bit işlemleri: AND, OR, XOR, SHL, SHR

---

*M-65 — Kendi işlemcini yazmak isteyenlere.*
