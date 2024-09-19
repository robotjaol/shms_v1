<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Tambah Data</title>
</head>
<body>
    <h2>Tambah Data</h2>
    <form action="insert_data1.php" method="post" enctype="multipart/form-data">
        <label for="name">Nama:</label><br>
        <input type="text" id="name" name="name" required><br>
        <label for="age">Umur:</label><br>
        <input type="number" id="age" name="age" required><br>
        <label for="email">Email:</label><br>
        <input type="email" id="email" name="email" required><br>
        <label for="photo">Foto:</label><br>
        <input type="file" id="photo" name="photo" required><br><br>
        <input type="submit" value="Tambah">
    </form>
</body>
</html>
