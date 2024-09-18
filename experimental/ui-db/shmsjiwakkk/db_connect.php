<?php
// db_connect.php
$servername = "localhost";
$username = "localhost";
$password = "";
$dbname = "databasecuy";

// Buat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Cek koneksi
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
?>