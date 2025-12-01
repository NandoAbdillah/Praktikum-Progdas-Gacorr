Berikut README yang **asik, santai, tapi tetap rapi dan enak dibaca** untuk project kelompokmu. Sudah aku kemas biar “gacorr, josjis”, dan cocok untuk laporan praktikum Progdas 🚀

---

# 🎫 Praktikum Progdas Gacorr – Aplikasi Tiketing Online

Halo! Selamat datang di repository **Praktikum Pemrograman Dasar Semester 1** yang dikerjakan oleh **Kelompok 5 – TI G 2025**.
Kelompok kami pastinya **gacorr**, **josjis**, **rajin menabung**, dan tentunya **berbakti pada orang tua** 

Project ini adalah implementasi materi Progdas Semester 1 seperti **kondisional, perulangan, array, fungsi, serta file handling**, yang kami kemas menjadi sebuah mini–aplikasi bernama:

# 🎟️ **Tiketku**

*Aplikasi pemesanan tiket online sederhana namun elegan.*

---

## 🌟 **Fitur Utama**

Aplikasi ini memiliki dua peran pengguna:

### 👤 **1. Pembeli**

Pengguna bisa melakukan hal-hal berikut:

* **Login**
* **Register akun baru**
* **Forgot Password** (via email / nomor telepon)
* **Beli tiket**
* **Cek saldo pengguna**
* **Cek status tiket**
* **Lihat riwayat pembelian**
* **Lihat & edit profil**
* **Ganti password**
* **Logout**

### 🛠️ **2. Admin**

Admin memiliki fitur manajerial:

* Melihat data user
* Melihat data tiket
* Menambahkan jadwal baru
* Mengubah harga/tarif kendaraan
* Logout

---

## 🧭 **Alur Program (Flow Program)**

### 🏠 **1. Menu Awal**

Tampilan pilihan:

* Login sebagai Pembeli
* Login sebagai Admin
* Register Pengguna Baru
* Forgot Password

---

## 👤 **Login & Register Pembeli**

### 🔐 Login:

* Masukkan username
* Masukkan password
* Cek kecocokan data

### 📝 Register:

Input data berikut:

* Nama lengkap
* Username
* Password
* Email
* Nomor telepon

### ❓ Forgot Password:

* Pilih reset via email/nomor telepon
* Masukkan kode OTP
* Masukkan password baru
* Konfirmasi password

---

## 💳 **Menu Pembeli**

Berisi fitur:

* **Beli tiket**
* **Saldo pengguna**
* **Cek status tiket**
* **Riwayat pembelian**
* **Profil**
* **Ganti password**
* **Logout**

---

## 🚆 **Beli Tiket**

### ✨ 1. Pilih kendaraan:

* Kereta Api
* Bus

---

### 🚆 **Kereta Api**

* Pilih rute

  * Surabaya Kota – Blitar
  * Surabaya Gubeng – Blitar (via Malang)
  * Surabaya Gubeng – Probolinggo
* Pilih kelas layanan & harga

  * Ekonomi – Rp200.000
  * Bisnis – Rp310.000
  * Eksekutif – Rp445.000
* Pilih jadwal (dd/mm/yy, jam)
* Pilih nomor kursi
* Tampilkan detail tiket
* Lanjutkan pembayaran

---

### 🚌 **Bus**

* Pilih rute

  * Bungurasih – Malang
  * Bungurasih – Probolinggo
  * Bungurasih – Kediri
* Pilih kelas layanan

  * Ekonomi – Rp80.000
  * AC Ekonomi – Rp100.000
  * Bisnis – Rp170.000
  * Eksekutif – Rp350.000
* Pilih jadwal
* Pilih kursi
* Lihat detail tiket
* Lanjutkan pembayaran

---

## 🔍 **Cek Status Tiket**

* Masukkan ID pembelian
* Tampilkan status:

  * **Aktif**
  * **Kadaluarsa**
  * **Tidak ditemukan**

---

## 🕓 **Riwayat Pembelian**

* Masukkan username
* Tampilkan daftar tiket yang pernah dibeli

---

## 🔐 **Ganti Password**

* Masukkan password lama
* Masukkan password baru
* Konfirmasi

---

# 🛠️ **Menu Admin**

### 📋 Lihat Data User

* Pilih kendaraan
* Tampilkan:

  * Nama lengkap
  * Username
  * Email
  * Password
  * Nomor telepon

### 🎫 Lihat Data Tiket

* Pilih kendaraan
* Pilih jadwal
* Tampilkan seluruh tiket yang terdaftar

### ➕ Tambah Jadwal

* Pilih kendaraan
* Tambahkan jadwal baru

### 💰 Ubah Tarif

* Pilih kendaraan
* Pilih jadwal
* Masukkan harga baru

---

# 📌 **Catatan Kelompok**

* Aplikasi ini menggunakan **file handling (fstream)** sebagai database sederhana.
* Semua fitur dibuat sebagai implementasi penuh materi Progdas Semester 1.
* Project dibuat oleh Kelompok 5 TI G.

---

Kalau ada bug… itu bukan bug. Itu *fitur mendadak* 😎🔥

---

Kalau kamu mau, bisa kubuatkan **versi markdown lengkap plus emoji**, atau **versi formal untuk laporan**.
