1. Fetch (Getir)
İşlemci, Program Counter (PC) adlı kayıtçısına bakar. PC, "Şu an belleğin hangi adresindeki komutu çalıştırmalıyım?" sorusunun cevabıdır. İşlemci, belleğin o adresine gider ve oradaki opcode'u (işlem kodunu) alıp kendi içine (Instruction Register) çeker.

2. Decode (Çöz)
İşlemci, getirdiği o gizemli sayının (opcode) ne anlama geldiğini çözer. "Bu bir toplama işlemi mi (ADD), yoksa belleğe bir şey yazma mı (STORE)?" diye kendi içindeki devrelere sorar. Bu aşama, komutun anlaşıldığı yerdir.

3. Execute (Çalıştır)
İşlemci, deşifre ettiği komutu yerine getirir. Eğer "topla" dediyse toplar, "belleğe yaz" dediyse yazar. İşlem bittikten sonra Program Counter (PC) bir artırılır ve işlemci bir sonraki komuta geçmeye hazır olur.
