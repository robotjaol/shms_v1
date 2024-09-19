<?php
$koneksi = new mysqli("localhost", "user", "user", "shms");

// Periksa koneksi
if ($koneksi->connect_error) {
    die("Koneksi gagal: " . $koneksi->connect_error);
}

// Inisialisasi variabel
$start_date = isset($_POST['start_date']) ? $_POST['start_date'] : '';
$end_date = isset($_POST['end_date']) ? $_POST['end_date'] : '';

$query = "SELECT * FROM log";

if ($start_date && $end_date) {
    $query .= " WHERE time BETWEEN '$start_date' AND '$end_date'";
}

$ambildata = mysqli_query($koneksi, $query);
?>
<!DOCTYPE html>
<html>
<head>
    <title>Data Log</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>
    <h2>Data Log</h2>
    
    <form method="POST">
        <label for="start_date">Start Date:</label>
        <input type="date" id="start_date" name="start_date" value="<?php echo $start_date; ?>">
        <label for="end_date">End Date:</label>
        <input type="date" id="end_date" name="end_date" value="<?php echo $end_date; ?>">
        <input type="submit" value="Filter">
    </form>

    <table border="1">
        <tr>
            <th>No</th>
            <th>Temperature</th>
            <th>Humidity</th>
            <th>Time</th>
            <th colspan="2">Aksi</th>
        </tr>

        <?php
        $no = 1;
        $temperatures = [];
        $humidities = [];
        $times = [];
        
        while ($tampil = mysqli_fetch_assoc($ambildata)) {
            echo "
            <tr>
                <td>$no</td>
                <td>{$tampil['temperature']}</td>
                <td>{$tampil['humidity']}</td>
                <td>{$tampil['time']}</td>
                <td><a href='?kode={$tampil['temperature']}'>Hapus</a></td>
                <td><a href='koneksi.php?kode={$tampil['temperature']}'>Ubah</a></td>
            </tr>";
            $no++;
            
            // Simpan data untuk chart
            $temperatures[] = $tampil['temperature'];
            $humidities[] = $tampil['humidity'];
            $times[] = $tampil['time'];
        }
        ?>

    </table>

    <h2>Chart Log</h2>
    <div>
        <canvas id="myChart"></canvas>
    </div>

    <script>
        // Mengambil data dari PHP ke JavaScript
        const temperatures = <?php echo json_encode($temperatures); ?>;
        const humidities = <?php echo json_encode($humidities); ?>;
        const times = <?php echo json_encode($times); ?>;
        
        // Inisialisasi chart
        const ctx = document.getElementById('myChart').getContext('2d');
        new Chart(ctx, {
            type: 'line',
            data: {
                labels: times, // Waktu sebagai label sumbu X
                datasets: [
                    {
                        label: 'Temperature',
                        data: temperatures,
                        borderColor: 'rgba(255, 99, 132, 1)',
                        borderWidth: 1,
                        fill: false
                    },
                    {
                        label: 'Humidity',
                        data: humidities,
                        borderColor: 'rgba(54, 162, 235, 1)',
                        borderWidth: 1,
                        fill: false
                    }
                ]
            },
            options: {
                scales: {
                    y: {
                        beginAtZero: true
                    }
                }
            }
        });
    </script>
</body>
</html>
