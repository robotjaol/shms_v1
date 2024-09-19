<?php 
    // buat koneksi ke database
    $konek = mysqli_connect("localhost", "user", "user","shms");
 
    // baca data dari tabel tb_sensor
    $sql = mysqli_query($konek, "select * from log order by id desc");
    //data terakhir ada di atas

    //baca data paling atas
    $data = mysqli_fetch_array($sql);
    $suhu = $data['temperature'];

    //uji, apabila nilai suhu belum ada, maka anggap suhu = 0
    if( $suhu == "" ) $suhu = 0;

    if ($suhu > 30) {
        echo "<span style='color: red;'>$suhu °C</span>"; // Teks berwarna merah
      } else if ($suhu <= 30) {
        echo "<span style='color: green;'>$suhu °C</span>"; // Teks berwarna hijau
      } else {
        echo $suhu . " ". $unit; // Teks tanpa warna (default)
      }

    

 
?>