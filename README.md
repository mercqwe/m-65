# M-65 - 8-Bit Custom CPU Emulator

BU BİR HOBİ ÖĞRENME PROJESİDİR

## Hakkında
Bu proje, kendi tasarladığım bir mimarinin yazılımsal olarak emüle edilmesidir. İşlemci mimarisini, "fetch-decode-execute" döngüsünü ve bellek yönetimini en temel seviyede öğrenmeyi hedefliyorum.

## Mimar Özellikleri
- **Bellek:** 16 Byte
- **Registerlar:** 
    - A (Accumulator)
    - PC (Program Counter)
    - F (Status Flags)
- **Komut Seti:** (İleride doldurulacak)

## Roadmap (Yapılacaklar)
- [ ] Dosya yapısı oluşturulacak
- [ ] Sistem nasıl çalışır öğrenilecek
- [ ] Memory dizisinin tanımlanması
- [ ] OpCode Matrix nedir öğrenilecek
- [ ] Emülatörün okuyabileceği formata çevrilebilecek bir tür assembly yazılmaya çalışılacak


## Dosya Yapısı (Umarım)
```text
M-65/
├── Makefile          # Derleme işlemlerini otomatize eden script
├── README.md         # Proje dokümantasyonu
├── src/              # Kaynak kodlar
│   ├── main.c        # Ana döngü (Fetch-Decode-Execute)
│   ├── cpu.c         # İşlemci mantığı ve register operasyonları
│   └── cpu.h         # Register tanımları ve fonksiyon prototipleri
└── bin/              # Derlenmiş binary dosyaları
```