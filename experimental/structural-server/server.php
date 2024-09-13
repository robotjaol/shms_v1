<?php
include("connection.php");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (isset($_POST["humidity"], $_POST["temperature"], $_POST["accelX"], $_POST["accelY"], $_POST["accelZ"], $_POST["gyroX"], $_POST["gyroY"], $_POST["gyroZ"])) {
          // Sanitize inputs using htmlspecialchars
        $humidity    = htmlspecialchars($_POST["humidity"], ENT_QUOTES, 'UTF-8');
        $temperature = htmlspecialchars($_POST["temperature"], ENT_QUOTES, 'UTF-8');
        $accelX      = htmlspecialchars($_POST["accelX"], ENT_QUOTES, 'UTF-8');
        $accelY      = htmlspecialchars($_POST["accelY"], ENT_QUOTES, 'UTF-8');
        $accelZ      = htmlspecialchars($_POST["accelZ"], ENT_QUOTES, 'UTF-8');
        $gyroX       = htmlspecialchars($_POST["gyroX"], ENT_QUOTES, 'UTF-8');
        $gyroY       = htmlspecialchars($_POST["gyroY"], ENT_QUOTES, 'UTF-8');
        $gyroZ       = htmlspecialchars($_POST["gyroZ"], ENT_QUOTES, 'UTF-8');

        if ($stmt = $conn->prepare("INSERT INTO db (humidity, temperature, accelX, accelY, accelZ, gyroX, gyroY, gyroZ) VALUES (?, ?, ?, ?, ?, ?, ?, ?)")) {
              // Bind parameters and execute
            $stmt->bind_param("ssssssss", $humidity, $temperature, $accelX, $accelY, $accelZ, $gyroX, $gyroY, $gyroZ);
            if ($stmt->execute()) {
                echo "Data successfully saved to the 'db' table.";
            } else {
                error_log("Execute Error: " . $stmt->error);
                echo "Error: Unable to save data.";
            }
            $stmt->close();
        } else {
            error_log("Prepare Error: " . $conn->error);
            echo "Error: Unable to prepare the query.";
        }
    } else {
        echo "Error: Incomplete POST data.";
    }
} else {
    echo "Error: Only POST requests are accepted.";
}

$conn->close();
?>
