<?php
$servername = "localhost";
$username = "root"; // ganti dengan username database Anda
$password = ""; // ganti dengan password database Anda
$dbname = "databasecuy"; // ganti dengan nama database Anda

// Membuat koneksi
$conn = new mysqli($servername, $username, $password, $dbname);

// Memeriksa koneksi
if ($conn->connect_error) {
    die("Koneksi gagal: " . $conn->connect_error);
}

// Memeriksa apakah form telah dikirimkan
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Mengambil data dari formulir
    $name = $_POST['name'] ?? '';
    $age = $_POST['age'] ?? '';
    $email = $_POST['email'] ?? '';
    
    // Mengambil file yang diunggah
    if(isset($_FILES["photo"]) && $_FILES["photo"]["error"] == 0) {
        $target_dir = "uploads/";
        $target_file = $target_dir . basename($_FILES["photo"]["name"]);
        $imageFileType = strtolower(pathinfo($target_file, PATHINFO_EXTENSION));
        $uploadOk = 1;

        // Memeriksa apakah file gambar adalah gambar asli atau bukan
        $check = getimagesize($_FILES["photo"]["tmp_name"]);
        if($check !== false) {
            $uploadOk = 1;
        } else {
            echo "File bukan gambar.";
            $uploadOk = 0;
        }

        // Memeriksa apakah file sudah ada
        if (file_exists($target_file)) {
            echo "Maaf, file sudah ada.";
            $uploadOk = 0;
        }

        // Memeriksa ukuran file
        if ($_FILES["photo"]["size"] > 5000000) {
            echo "Maaf, file Anda terlalu besar.";
            $uploadOk = 0;
        }

        // Memeriksa format file
        if($imageFileType != "jpg" && $imageFileType != "png" && $imageFileType != "jpeg"
        && $imageFileType != "gif" ) {
            echo "Maaf, hanya JPG, JPEG, PNG & GIF yang diperbolehkan.";
            $uploadOk = 0;
        }

        // Memeriksa apakah $uploadOk adalah 0 karena kesalahan
        if ($uploadOk == 0) {
            echo "Maaf, file Anda tidak terunggah.";
        // Jika semua hal diperiksa, coba unggah file
        } else {
            if (move_uploaded_file($_FILES["photo"]["tmp_name"], $target_file)) {
                echo "File ". htmlspecialchars( basename( $_FILES["photo"]["name"])). " telah diunggah.";
                // Menyiapkan pernyataan SQL
                $sql = "INSERT INTO users (name, age, email, photo) VALUES ('$name', '$age', '$email', '$target_file')";

                if ($conn->query($sql) === TRUE) {
                    echo "Data berhasil ditambahkan";
                } else {
                    echo "Error: " . $sql . "<br>" . $conn->error;
                }
            } else {
                echo "Maaf, terjadi kesalahan saat mengunggah file Anda.";
            }
        }
    } else {
        echo "Tidak ada file yang diunggah atau terjadi kesalahan.";
    }
} else {
    echo "Formulir tidak disubmit dengan benar.";
}

// Menutup koneksi
$conn->close();
?>
