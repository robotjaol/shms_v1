<?php
$servername = "localhost";  // Jika PHP berjalan di server yang sama dengan database
$username = "root";         // Username database
$password = "";             // Password database
$dbname = "sensor_data";    // Nama database

// Membuat koneksi ke database
$conn = new mysqli($servername, $username, $password, $dbname);

// Memeriksa koneksi
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Mendapatkan data dari POST
$suhu = $_POST['suhu'];
$kelembaban = $_POST['kelembaban'];

// Validasi data sebelum memasukkan ke database
if (isset($suhu) && isset($kelembaban)) {
    // Menyimpan data ke tabel
    $sql = "INSERT INTO data_suhu_kelembaban (suhu, kelembaban) VALUES ('$suhu', '$kelembaban')";

    if ($conn->query($sql) === TRUE) {
        echo "Data berhasil disimpan!";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "Data suhu atau kelembaban tidak tersedia.";
}

$conn->close();
