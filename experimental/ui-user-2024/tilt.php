<?php
// Establish a connection to the database
$koneksi = new mysqli("localhost", "user", "user", "shms");

// Check the connection
if ($koneksi->connect_error) {
    die("Connection failed: " . $koneksi->connect_error);
}

// Initialize variables for date filtering
$start_date = isset($_POST['start_date']) ? $_POST['start_date'] : '';
$end_date = isset($_POST['end_date']) ? $_POST['end_date'] : '';

$query = "SELECT * FROM log_akselero";
$params = [];
$types = '';

// Modify query and parameters if date filters are provided
if ($start_date && $end_date) {
    $query .= " WHERE waktu BETWEEN ? AND ?"; // Change 'time' to 'waktu'
    $params[] = $start_date;
    $params[] = $end_date;
    $types .= 'ss';
}

$stmt = $koneksi->prepare($query);

// Check if prepare() failed
if ($stmt === false) {
    die("Failed to prepare statement: " . $koneksi->error);
}

// Bind parameters if available
if (!empty($params)) {
    // Check if bind_param failed
    if (!$stmt->bind_param($types, ...$params)) {
        die("Parameter binding failed: " . $stmt->error);
    }
}

// Execute the query
if (!$stmt->execute()) {
    die("Query execution failed: " . $stmt->error);
}

$ambildata = $stmt->get_result();

// Initialize arrays to hold the data
$x = [];
$y = [];
$z = [];
$times = [];

// Fetch data into arrays
while ($tampil = $ambildata->fetch_assoc()) {
    $x[] = $tampil['x'];
    $y[] = $tampil['y'];
    $z[] = $tampil['z'];
    $times[] = $tampil['waktu']; // Ensure this matches the column name in your table
}

// Close the statement and connection
$stmt->close();
$koneksi->close();
?>


<!DOCTYPE html>
<html lang="en">
<head>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
    <meta name="description" content="" />
    <meta name="author" content="" />
    <title>Website Monitoring</title>
    <link href="styles.css" rel="stylesheet" />
    <link href="https://cdn.datatables.net/1.10.20/css/dataTables.bootstrap4.min.css" rel="stylesheet" crossorigin="anonymous" />
    <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/js/all.min.js" crossorigin="anonymous"></script>
    <style>
        body { margin: 0; }
        canvas { display: block; }
    </style>
</head>
<body class="sb-nav-fixed">
    <nav class="sb-topnav navbar navbar-expand navbar-dark bg-dark">
        <a class="navbar-brand" href="home.php"><div id="time-date"></div>
            <script src="date.js"></script></a>
        <button class="btn btn-link btn-sm order-1 order-lg-0" id="sidebarToggle" href="#"><i class="fas fa-bars"></i></button> 
    </nav>
    <div id="layoutSidenav">
        <div id="layoutSidenav_nav">
            <nav class="sb-sidenav accordion sb-sidenav-dark" id="sidenavAccordion">
                <div class="sb-sidenav-menu">
                    <div class="nav">
                        <div class="sb-sidenav-menu-heading"></div>
                        <a class="nav-link" href="home.php">
                            <div class="sb-nav-link-icon"><i class="fas fa-tachometer-alt"></i></div>
                            Dashboard
                        </a>
                        
                        <div class="sb-sidenav-menu-heading">History</div>
                        <a class="nav-link" href="charts.php">
                            <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                            Humidity & Temperature
                        </a>
                        <a class="nav-link" href="tilt.php">
                            <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                            Tilt
                        </a>
                        <a class="nav-link" href="aboutus.php">
                            <div class="sb-nav-link-icon"><i class="fas fa-address-card"></i></div>
                            About Us
                        </a>
                    </div>
                </div>
            </nav>
        </div>
        <div id="layoutSidenav_content">
            <main>
                <div class="container-fluid">
                    <center>
                        <h1 class="mt-4">Tilt</h1>
                    </center>
                    
                    <ol class="breadcrumb mb-4">
                        <li class="breadcrumb-item"><a href="home.php">Dashboard</a></li>
                        <li class="breadcrumb-item active">Tilt</li>
                    </ol>
                    
                    <div class="card mb-4">
                        <div class="card-header">
                            <i class="fas fa-table mr-1"></i>
                            History Logs
                            <form method="POST">
                                <label for="start_date">Start Date:</label>
                                <input type="date" id="start_date" name="start_date" value="<?php echo $start_date; ?>">
                                <label for="end_date">End Date:</label>
                                <input type="date" id="end_date" name="end_date" value="<?php echo $end_date; ?>">
                                <input type="submit" value="Filter">
                            </form>
                            <button id="toggleTableBtn">Show Table</button>
                        </div>
                        <div class="card-body">
                            <div class="table-responsive" id="dataTableContainer" style="display: none;">
                                <table class="table table-bordered" id="dataTable" width="100%" cellspacing="0">
                                    <thead>
                                        <tr>
                                            <th>No</th>
                                            <th>X</th>
                                            <th>Y</th>
                                            <th>Z</th>
                                            <th>Time</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <?php
                                        $no = 1;
                                        foreach ($x as $index => $value) {
                                            echo "
                                            <tr>
                                                <td>$no</td>
                                                <td>{$x[$index]}</td>
                                                <td>{$y[$index]}</td>
                                                <td>{$z[$index]}</td>
                                                <td>{$times[$index]}</td>
                                            </tr>";
                                            $no++;
                                        }
                                        ?>
                                    </tbody>
                                </table>
                            </div>

                            <div>
                                <canvas id="myChart"></canvas>
                            </div>

                            <script>
                                // Mengambil data dari PHP ke JavaScript
                                const xData = <?php echo json_encode($x); ?>;
                                const yData = <?php echo json_encode($y); ?>;
                                const zData = <?php echo json_encode($z); ?>;
                                const times = <?php echo json_encode($times); ?>;

                                // Inisialisasi chart
                                const ctx = document.getElementById('myChart').getContext('2d');
                                new Chart(ctx, {
                                    type: 'line',
                                    data: {
                                        labels: times, // Waktu sebagai label sumbu X
                                        datasets: [
                                            {
                                                label: 'X',
                                                data: xData,
                                                borderColor: 'rgba(255, 0, 0, 1)',
                                                borderWidth: 1,
                                                fill: false
                                            },
                                            {
                                                label: 'Y',
                                                data: yData,
                                                borderColor: 'rgba(90, 255, 0, 1)',
                                                borderWidth: 1,
                                                fill: false
                                            },
                                            {
                                                label: 'Z',
                                                data: zData,
                                                borderColor: 'rgba(0, 90, 200, 1)',
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

                                // Script untuk sembunyikan/tampilkan tabel
                                const toggleTableBtn = document.getElementById('toggleTableBtn');
                                const dataTableContainer = document.getElementById('dataTableContainer');

                                toggleTableBtn.addEventListener('click', () => {
                                    if (dataTableContainer.style.display === 'none') {
                                        dataTableContainer.style.display = 'block';
                                        toggleTableBtn.textContent = 'Hide Table';
                                    } else {
                                        dataTableContainer.style.display = 'none';
                                        toggleTableBtn.textContent = 'Show Table';
                                    }
                                });
                            </script>
                        </div>
                    </div>
                </div>
            </main>
        </div>
    </div>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js" crossorigin="anonymous"></script>
    <script src="js/scripts.js"></script>
    <script src="https://cdn.datatables.net/1.10.20/js/jquery.dataTables.min.js" crossorigin="anonymous"></script>
    <script src="https://cdn.datatables.net/1.10.20/js/dataTables.bootstrap4.min.js" crossorigin="anonymous"></script>
    <script src="assets/demo/chart-line-demo.js"></script>
    <script src="assets/demo/datatables-demo.js"></script>
</body>
</html>
