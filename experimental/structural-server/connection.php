<?php
    // Declare the variables
$servername = "localhost";
$username   = "root";
$password   = "";
$dbname     = "shms";

    // Create a new mysqli instance
$conn = new mysqli($servername, $username, $password, $dbname);

    // Check the connection
if ($conn->connect_error) {
    die("Failed to connect to MySQL: " . $conn->connect_error);
}

?>
