# Automatic Cat Feeder with PID Control

Proyek ini adalah sistem pemberi makan otomatis untuk kucing yang menggunakan sensor berat (Load Cell) dan kontrol PID untuk memastikan pakan yang diberikan sesuai dengan target berat tertentu. Sistem ini juga memanfaatkan sensor ultrasonik untuk mendeteksi jarak, servo motor untuk mengatur pembukaan katup dispenser, serta dilengkapi dengan **Linear Actuator Servo Extension** untuk pengaturan yang lebih presisi.

---

## Fitur
- **Kontrol PID**: Menjamin akurasi pemberian pakan sesuai target berat.
- **Load Cell**: Untuk mengukur berat pakan yang diberikan.
- **Sensor Ultrasonik**: Mendeteksi keberadaan hewan.
- **Servo Motor**: Mengatur pembukaan katup tempat pakan.
- **Linear Actuator Servo Extension**: Memberikan gerakan linier untuk pengaturan buka tutup katup yang lebih presisi.

---

## Komponen yang Digunakan
1. **Arduino Board** (contoh: Arduino Uno)
2. **Load Cell** dan **HX711 Module**
3. **Servo Motor**
4. **Linear Actuator Servo Extension**
5. **Sensor Ultrasonik** (HC-SR04)
6. Komponen tambahan seperti kabel jumper, breadboard, dan sumber daya.

---

## Cara Kerja
1. **Deteksi Jarak**: Sensor ultrasonik memeriksa keberadaan kucing.
2. **Pengukuran Berat**: Load cell membaca berat pakan yang tersedia.
3. **Kontrol PID**:
   - Menghitung error antara berat aktual dan berat target.
   - Mengatur sudut servo dan linear actuator untuk mengontrol aliran pakan berdasarkan output PID.
4. **Pemberian Pakan**: Jika berat target tercapai, servo motor dan linear actuator menutup katup tempat pakan.

---

## Instalasi dan Penggunaan
1. Hubungkan komponen seperti pada skema rangkaian.
2. Unggah file `AUTOMATIC-CAT-FEEDER-WITH-PID.ino` ke Arduino Anda.
3. Atur nilai kalibrasi Load Cell pada bagian kode:
   ```cpp
   LoadCell.setCalFactor(427);  // Sesuaikan nilai kalibrasi sesuai kebutuhan
