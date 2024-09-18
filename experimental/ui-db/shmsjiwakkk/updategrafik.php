<?php
$koneksi = new mysqli("localhost", "root", "", "databasecuy");

if ($koneksi->connect_error) {
    die("Koneksi gagal: " . $koneksi->connect_error);
}

$start_date = isset($_POST['start_date']) ? $_POST['start_date'] : '';
$end_date = isset($_POST['end_date']) ? $_POST['end_date'] : '';

$query = "SELECT * FROM log";
$params = [];
$types = '';

if ($start_date && $end_date) {
    $query .= " WHERE time BETWEEN ? AND ?";
    $params[] = $start_date;
    $params[] = $end_date;
    $types .= 'ss';
}

$stmt = $koneksi->prepare($query);
if (!empty($params)) {
    $stmt->bind_param($types, ...$params);
}
$stmt->execute();
$ambildata = $stmt->get_result();

$data = [];
while ($tampil = $ambildata->fetch_assoc()) {
    $data[] = $tampil;
}

$stmt->close();
$koneksi->close();

echo json_encode($data);
?>
