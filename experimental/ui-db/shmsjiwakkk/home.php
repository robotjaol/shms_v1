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
                    $("#ceksuhu_lt2").load("ceksuhu_lt2.php");
                }, 1000 );
                setInterval( function() {
                    $("#cekkelembaban").load("cekkelembaban.php");
                }, 1000 );
                setInterval( function() {
                    $("#cekkelembaban_lt2").load("cekkelembaban_lt2.php");
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

.background-image {
            background-image: url('gedung2.png');
            background-size: cover; /* Menyesuaikan ukuran gambar agar sesuai dengan div */
            background-position: center; /* Memposisikan gambar di tengah div */
            padding: 20px;
            border: 1px solid #ccc;
            height: 800px; /* Atur tinggi agar gambar dapat terlihat */
            color: white; /* Atur warna teks agar terlihat */
            z-index: 0;
        }

        .nav-container {
    display: flex;
    justify-content: center; /* Atur untuk menjajarkan ke kanan */
}

.nav-link {
    margin-left: 10px; /* Jarak antar button */
    text-decoration: none;
    color: black; /* Warna teks, sesuaikan dengan kebutuhan */
}


1

   *,
    *::after,
    *::before {
        padding: inherit;
        margin: inherit;
        box-sizing: inherit;
    }
 
    html {
        padding: 0;
        margin: 0;
        box-sizing: border-box;
    }
 
    body {
        --color: #fff;
        --hover-b: #000;
        --hover-w: #fff;
        display: grid;
        place-content: flex;
        background-color: rgb(255, 255, 255);
        width: 100vw;
        height: 100vh
    }
 
    .btn1 {
        background: none;
        border: 4px solid var(--color);
        padding: 0.8em 1em;
        margin: 6.5em;
        user-select: none;
        text-transform: uppercase;
        color: var(--color);
        letter-spacing: 2.2px;
        cursor: pointer;
        border-radius: 30px;
        transform: translateY(0);
        transition: all 0.5s linear;
    }
 
    /* the inset brings the box-shadow from the inside */
    .window_slide:hover {
        box-shadow: inset 8rem 0 0 0 var(--color), inset -8rem 0 0 0 var(--color);
        color: var(--hover-b);
        transform: translateY(-0.5rem);
 
    }
 
    .popup:hover {
        box-shadow: 0rem 0.99rem 0.43rem -0.33rem var(--color);
        transform: translateY(-0.5rem);
    }
 
    .slidein:hover {
        box-shadow: inset 0 0 0.5rem 4em var(--color);
        transform: translateY(-0.5rem);
        color: var(--hover-b);
    }
 
    .burst:hover {
        box-shadow: 0 0 1.1rem 8px var(--color);
        transform: translateY(-0.5rem);
    }
 
    @media only screen and (max-width: 1080px) {
    div {
        display: grid;
        grid-template-columns: repeat(2, auto);
    }
 
}
 
    @media only screen and (max-width: 600px) {
    div {
        display: grid;
        grid-template-columns: repeat(1, auto);
    }
 
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
                            <a class="nav-link" href="charts.php">
                                <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                                Humidity & Temperature
                            </a>
                            <a class="nav-link" href="tilt.php">
                                <div class="sb-nav-link-icon"><i class="fas fa-table"></i></div>
                                Tilt
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
                            <h1 class="mt-4">STRUCTURAL HEALTH MONITORING SYSTEM</h1>
                        </center>
                     
                        <ol class="breadcrumb mb-4">
                            <li class="breadcrumb-item active">Dashboard</li>
                        </ol>
                        <!-- Tombol 1 --><div>
                        <div class="nav-container">
    
</div>
    </div>
                        
</script>

                        <div class="row">
                            <div class="col-xl-6">
                                <div class="card mb-4">
                                    <div class="card-header">
                                        <i class="fas fa-chart-area mr-1"></i>
                                        Chart
                                    </div>
                                    <div class="background-image">
                                    <div class="nav-container">
                                    <div>
            <div class="button">
                <div>
                <a href="home3.php" >
                    <button class="btn1 window_slide"><b>Lantai 3</b></button><br>
                </a>
                <a href="home2.php" >
                    <button class="btn1 window_slide"><b>Lantai 2</b></button><br>
                </a>
                <a href="home.php" >
                    <button class="btn1 window_slide"><b>Lantai 1</b></button><br>
                </a>
                </div>
            </div>
        </div>
</div>
    </div>
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
                                            <h3> <span id="ceksuhu_lt2"> 0 </span> </h3>
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
                                            X
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

                                    
                                    <!-- Tabel Akhir Menampilkan nilai Suhu --> 
                                    <!DOCTYPE html>


    

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
 