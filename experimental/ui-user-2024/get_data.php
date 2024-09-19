<?php
// get_data.php
include 'fetchData.php';

$month = isset($_GET['month']) ? $_GET['month'] : date('m'); // Default bulan saat ini

$sql = "SELECT temperature, humidity, waktu FROM log WHERE MONTH(waktu) = ?";
$stmt = $conn->prepare($sql);
$stmt->bind_param("i", $month);
$stmt->execute();
$result = $stmt->get_result();

$data = array();
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}

echo json_encode($data);
?>