<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="X-UA-Compatible" content="IE=edge" />
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
        <meta name="description" content="" />
        <meta name="author" content="" />
        <title>Website Monitoring</title>
        <link href="styles.css" rel="stylesheet" />
        <link href="https://cdn.datatables.net/1.10.20/css/dataTables.bootstrap4.min.css" rel="stylesheet" crossorigin="anonymous" />
        <script src="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/js/all.min.js" crossorigin="anonymous"></script>

        <script type="text/javascript" src="jquery/jquery.min.js"></script>
        <!--load otomatis/ realtime-->
        <script type="text/javascript">
            $(document).ready(function() {

                setInterval( function() {
                    $("#ceksuhu").load("ceksuhu.php");
                }, 1000 );

                setInterval( function() {
                    $("#cekkelembaban").load("cekkelembaban.php");
                }, 1000 );

                setInterval( function() {
                    $("#cekakselerox").load("cekakselerox.php");
                }, 1000 );

                setInterval( function() {
                    $("#cekakseleroy").load("cekakseleroy.php");
                }, 1000 );

                setInterval( function() {
                    $("#cekakseleroz").load("cekakseleroz.php");
                }, 1000 );

            } );

        </script> 
        <style>
        .button {
            background-color: #4CAF50; /* Warna latar belakang hijau */
            border: none;
            color: white; /* Warna teks putih */
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 16px;
            margin: 4px 2px;
            cursor: pointer;
            border-radius: 4px; /* Membuat sudut tombol melengkung */
        }

        .button:hover {
            background-color: #45a049; /* Warna latar belakang saat hover */
        }
        </style>
        

    </head>
    <body class="sb-nav-fixed">
               
        <nav class="sb-topnav navbar navbar-expand navbar-dark bg-dark">
            <a class="navbar-brand" href="index.html"><div id="time-date"></div>
                <script src="date.js"></script> </a>
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
                            <a class="nav-link" href="charts.html">
                                <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                                Humidity & Temperature
                            </a>
                            <a class="nav-link" href="tables.html">
                                <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                                Tilt
                            <a class="nav-link" href="aboutus.html">
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
                            <h1 class="mt-4">STRUCTURAL HEALTH MONITORING SYSTEM</h1>
                        </center>
                     
                        <ol class="breadcrumb mb-4">
                            <li class="breadcrumb-item active">Dashboard</li>
                        </ol>
                        <!-- Tombol 1 -->
                        <button class="button" onclick="buttonClicked('https://www.instagram.com')">Tombol 1</button>

                        <!-- Tombol 2 -->
                            <button class="button" onclick="buttonClicked('https://www.facebook.com')">Tombol 2</button>

                        <!-- Tombol 3 -->
                        <button class="button" onclick="buttonClicked('https://www.google.com')">Tombol 3</button>
                        <script>
                        function buttonClicked(url) {
                        window.location.href = url; // Ganti URL dengan tujuan yang diinginkan
                        }
</script>
                        <!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Presentase Kesehatan Gedung</title>
    <link rel="stylesheet" href="gkesehatan.css"> <!-- Import CSS untuk styling -->
</head>
<body>
    <div class="container">
        <h1>Presentase Kesehatan Gedung</h1>
        <div class="health-status">
            <div class="category">
                <h2>Layak Huni</h2>
                <div class="percentage">70%</div>
            </div>
            <div class="category">
                <h2>Perlu Perbaikan</h2>
                <div class="percentage">20%</div>
            </div>
            <div class="category">
                <h2>Tidak Layak Huni</h2>
                <div class="percentage">10%</div>
            </div>
        </div>
    </div>
</body>
</html>

                        <div class="row">
                            <div class="col-xl-6">
                                <div class="card mb-4">
                                    <div class="card-header">
                                        <i class="fas fa-chart-area mr-1"></i>
                                        Chart
                                    </div>
                                    <div class="card-body"><canvas id="myDoughnutchart" width="400" height="200"></canvas></div>
                                </div>
                            </div>
                            <div class="col-xl-6">
                                <div class="card mb-4">
                                <div class="card-header">
                                        <i class="fas fa-chart-area mr-1"></i>
                                        Realtime Monitoring
                                </div>                                       
                                    <div class="card-body">
                                    <div style="display: flex;">
                                    <!-- Tabel Menampilkan nilai Suhu -->
                                    <div class="card text-center" style="width: 50%">
                                        <div class="card-header"> 
                                            <i class="fas fa-chart-area mr-1"></i>
                                            Suhu
                                        </div>
                                        <div class="card-body">
                                            <h3> <span id="ceksuhu"> 0 </span> </h3>
                                        </div>
                                             
                                        </div>
                                        <!-- Tabel Akhir Menampilkan nilai Suhu --> 
                                        
                                        <!-- Tabel Menampilkan nilai Suhu -->
                                        <div class="card text-center" style="width: 50%">
                                            <div class="card-header" > 
                                                <i class="fas fa-chart-area mr-1"></i>
                                                Kelembaban
                                            </div>
                                                <div class="card-body">
                                                    <h3> <span id="cekkelembaban"> 0 </span> % </h3>
                                                </div>
                                             
                                        </div>
                                        <!-- Tabel Akhir Menampilkan nilai Suhu --> 
                                        </div>
                                    </div>

                                    <div class="card-body">
                                    <div style="display: flex;">
                                    <!-- Tabel Menampilkan nilai Suhu -->
                                    <div class="card text-center" style="width: 50%">
                                        <div class="card-header"> 
                                            <i class="fas fa-chart-area mr-1"></i>
                                            X data
                                        </div>
                                        <div class="card-body" style="color: white;">
                                            <h3> <span id="cekakselerox"> 0 </span> degree </h3>
                                        </div>
                                             
                                    </div>
                                    <!-- Tabel Akhir Menampilkan nilai Suhu --> 
                                        
                                        <!-- Tabel Menampilkan nilai Suhu -->
                                        <div class="card text-center" style="width: 50%">
                                            <div class="card-header" > 
                                                <i class="fas fa-chart-area mr-1"></i>
                                                Y
                                            </div>
                                                <div class="card-body" style="color: white;">
                                                    <h3> <span id="cekakseleroy"> 0 </span> degree </h3>
                                                </div>
                                             
                                        </div>
                                        <!-- Tabel Akhir Menampilkan nilai Suhu --> 

                                    <!-- Tabel Menampilkan nilai Suhu -->
                                    <div class="card text-center" style="width: 50%">
                                        <div class="card-header"> 
                                            <i class="fas fa-chart-area mr-1"></i>
                                            Z
                                        </div>
                                        <div class="card-body" style="color: white;">
                                            <h3> <span id="cekakseleroz"> 0 </span> degree </h3>
                                        </div>
                                             
                                    </div>
                                    <!-- Tabel Akhir Menampilkan nilai Suhu --> 

                                    </div>
                                    </div>
                                  
                                </div>
                            </div>
                        </div>
                    
                        
                                    
                                </div>
                            </div>
                        </div>
                
            </div>
        </div>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js" crossorigin="anonymous"></script>
        <script src="js/scripts.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.8.0/Chart.min.js" crossorigin="anonymous"></script>
        <script src="assets/demo/chart-doughnut-demo.js"></script>
        <script src="https://cdn.datatables.net/1.10.20/js/jquery.dataTables.min.js" crossorigin="anonymous"></script>
        <script src="https://cdn.datatables.net/1.10.20/js/dataTables.bootstrap4.min.js" crossorigin="anonymous"></script>
        <script src="assets/demo/datatables-demo.js"></script>
    </body>
</html>
 