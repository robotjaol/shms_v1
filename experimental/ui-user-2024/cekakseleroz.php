<?php 
    // buat koneksi ke database
    $konek = mysqli_connect("localhost", "user", "user","shms");
 
    // baca data dari tabel tb_sensor
    $sql = mysqli_query($konek, "select * from log_akselero order by id desc");
    //data terakhir ada di atas

    //baca data paling atas
    $data = mysqli_fetch_array($sql);
    $z = $data['z'];

    //uji, apabila nilai suhu belum ada, maka anggap suhu = 0
    if( $z == "" ) $z = 0;

    //print suhu
    echo $z ;
 
?>