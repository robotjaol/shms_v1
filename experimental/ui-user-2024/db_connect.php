<?php
// db_connect.php
$servername = "localhost";
$username = "user";
$password = "user";
$dbname = "shms";

// Buat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>