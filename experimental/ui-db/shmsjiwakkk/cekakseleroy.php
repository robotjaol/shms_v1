<?php 
    // buat koneksi ke database
    $konek = mysqli_connect("localhost", "root", "","databasecuy");
 
    // baca data dari tabel tb_sensor
    $sql = mysqli_query($konek, "select * from log_akselero order by id desc");
    //data terakhir ada di atas

    //baca data paling atas
    $data = mysqli_fetch_array($sql);
    $y = $data['y'];

    //uji, apabila nilai suhu belum ada, maka anggap suhu = 0
    if( $y == "" ) $y = 0;

    //print suhu
    echo $y ;
 
?>