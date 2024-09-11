//connection
<?php
// Declare the variables
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "structural_health_db";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_errno) {
  die("Failed to connect to MySQL: " . $conn->connect_error);
}
?>
