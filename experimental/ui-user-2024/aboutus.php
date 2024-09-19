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
        <script>
        function showDonateMessage() {
            alert("Donasi dapat dikirim ke rekening :\nBCA 3890679381 \nA.N. Akhmad Anugrah Jiwangga.\nTerimakasih. \u2764️");
        }
    </script>
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
                            <a class="nav-link" href="aboutus.php">
                                 <div class="sb-nav-link-icon"><i class="fas fa-address-card"></i></div>
                                About Us
                            </a>
                            <a class="nav-link" href="#" onclick="showDonateMessage()">
                                <div class="sb-nav-link-icon"><i class="fas fa-donate"></i></div>
                                Donate
                            </a>

                        </div>
                    </div>
                    
                </nav>
            </div>
            <div id="layoutSidenav_content">
                <main>
                    <div class="container-fluid">
                        <center>
                            <h1 class="mt-4">About Us</h1>
                        </center>
                       
                        <ol class="breadcrumb mb-4">
                            <li class="breadcrumb-item"><a href="home.php">Dashboard</a></li>
                            <li class="breadcrumb-item active">About Us</li>
                        </ol>
                        
                        <div class="card mb-4">
                            <head>
                                <meta charset="UTF-8">
                                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                                <title>About Us</title>
                                <style>
                                    body {
                                        font-family: Arial, sans-serif;
                                        margin: 0;
                                        padding: 0;
                                    }
                                    .container {
                                        max-width: 800px;
                                        margin: 20px auto;
                                        padding: 0 20px;
                                    }
                                    h1 {
                                        text-align: center;
                                    }
                                    .about-text {
                                        text-align: justify;
                                        margin-bottom: 20px;
                                    }
                                    .profile-img {
                                        display: block;
                                        margin: 0 auto;
                                        max-width: 100%;
                                        height: auto;
                                    }
                                    .button-container {
                                        display: flex;
                                        justify-content: space-around;
                                        margin-top: 20px;
                                    }
                                </style>
                            </head>
                            <div class="container">
                                <h1>Our Love &#129505</h1>
                                <div class="about-text">
                                    <p>Welcome to our website! We are a team of passionate individuals dedicated to providing high-quality services/products. Our mission is to make a positive impact on the world by build this monitoring system for building's health.</p>
                                    <p>Feel free to contact us if you have any questions or inquiries. We are always here to assist you! &#128170</p>
                                </div>
                                <div class="profile">
                                    <img src="profile.jpg" alt="Our Team" class="profile-img">
                                </div>
                                
                                <div class="button-container">
                                    <button onclick="window.open('https://www.instagram.com/icyyocyy', '_blank')" class="btn btn-primary">Rosy</button>
                                    <button onclick="window.open('https://www.instagram.com/retha.ndz', '_blank')" class="btn btn-primary">Aretha</button>
                                    <button onclick="window.open('https://www.instagram.com/balqismahiraa', '_blank')" class="btn btn-primary">Balqis</button>
                                    <button onclick="window.open('https://www.instagram.com/jiwangga._', '_blank')" class="btn btn-primary">Jiwangga</button>
                                    <button onclick="window.open('https://www.instagram.com/bariqnizam', '_blank')" class="btn btn-primary">Bariq</button>
                                    <button onclick="window.open('https://www.instagram.com/amir.zufar', '_blank')" class="btn btn-primary">Amir</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </main>
                <div id="audio-player">
                    <audio controls autoplay>
                      <source src="lagu.mp3" type="audio/mpeg">
                    </audio>
                  </div>
            </div>
        </div>
        
        <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js" crossorigin="anonymous"></script>
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js" crossorigin="anonymous"></script>
        <script src="js/scripts.js"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.8.0/Chart.min.js" crossorigin="anonymous"></script>
        <script src="https://cdn.datatables.net/1.10.20/js/jquery.dataTables.min.js" crossorigin="anonymous"></script>
        <script src="https://cdn.datatables.net/1.10.20/js/dataTables.bootstrap4.min.js" crossorigin="anonymous"></script>
        <script src="assets/demo/chart-line-demo.js"></script>
        <script src="assets/demo/datatables-demo.js"></script>
    </body>
</html>
