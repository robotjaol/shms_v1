<?php
require_once 'vendor/autoload.php'; // Load the Twilio SDK

use Twilio\Rest\Client;

// Database connection
$konek = mysqli_connect("localhost", "root", "", "databasecuy");

if (!$konek) {
    die("Connection failed: " . mysqli_connect_error());
}

// Read data from the table 'log'
$sql = mysqli_query($konek, "SELECT * FROM log ORDER BY id DESC LIMIT 1");

if ($data = mysqli_fetch_array($sql)) {
    $suhu = $data['temperature'];
} else {
    $suhu = 0;
}

if ($suhu == "") $suhu = 0;

// Set Twilio credentials
$sid = 'AC46faa6c1f6f2c135a0b4d8956852a910';
$token = 'f5692b6eb7abc949f8aebd166ca515c0';
$twilioNumber = 'whatsapp:+14155238886'; // Twilio sandbox number for WhatsApp
$toNumber = 'whatsapp:+6285727648461'; // Recipient's WhatsApp number

$client = new Client($sid, $token);

// Create the message content
if ($suhu > 30) {
    $messageContent = "Temperature Alert: $suhu °C. The temperature is above the safe limit.";
} else {
    $messageContent = "Suhu saat ini: $suhu °C. \nJangan Lupa Follow IG : jiwangga._";
}

// Send the WhatsApp message
$message = $client->messages->create(
    $toNumber,
    [
        'from' => $twilioNumber,
        'body' => $messageContent
    ]
);

echo "Message sent!";
mysqli_close($konek);
?>
