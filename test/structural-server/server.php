// Server 
<?php
include("connection.php");

if (!empty($_POST)) {
    // POST request DATA sensor 
  $humidity    = $_POST["kelembaban"];
  $temperature = $_POST["suhu"];
  $accelX      = $_POST["accelX"];
  $accelY      = $_POST["accelY"];
  $accelZ      = $_POST["accelZ"];
  $gyroX       = $_POST["gyroX"];
  $gyroY       = $_POST["gyroY"];
  $gyroZ       = $_POST["gyroZ"];

  $query = "INSERT INTO data (kelembaban, suhu, accelX, accelY, accelZ, gyroX, gyroY, gyroZ) 
            VALUES ('" . $humidity . "', '" . $temperature . "', '" . $accelX . "', '" . $accelY . "', '" . $accelZ . "', '" . $gyroX . "', '" . $gyroY . "', '" . $gyroZ . "')";
  
    // Re-check data output
  if ($conn->query($query) === TRUE) {
    echo "Berhasil menyimpan data ke tabel db";
  } else {
    echo "Error: " . $query . "<br>" . $conn->error;
  }
  $conn->close();
}
?>
