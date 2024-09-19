<!DOCTYPE html>
<html>
<head>
    <title>Data Table</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <style>
        table {
            width: 100%;
            border-collapse: collapse;
        }
        table, th, td {
            border: 1px solid black;
        }
        th, td {
            padding: 8px;
            text-align: left;
        }
        th {
            background-color: #f2f2f2;
        }
    </style>
</head>
<body>

<h2>Pilih Bulan</h2>
<form id="monthForm">
    <label for="month">Bulan:</label>
    <select id="month" name="month">
        <option value="1">Januari</option>
        <option value="2">Februari</option>
        <option value="3">Maret</option>
        <option value="4">April</option>
        <option value="5">Mei</option>
        <option value="6">Juni</option>
        <option value="7">Juli</option>
        <option value="8">Agustus</option>
        <option value="9">September</option>
        <option value="10">Oktober</option>
        <option value="11">November</option>
        <option value="12">Desember</option>
    </select>
    <button type="submit">Tampilkan</button>
</form>

<table id="dataTable">
    <thead>
        <tr>
            <th>Waktu</th>
            <th>Temperature</th>
            <th>Humidity</th>
        </tr>
    </thead>
    <tbody>
        <!-- Data akan diisi melalui JavaScript -->
    </tbody>
</table>

<script>
document.getElementById('monthForm').addEventListener('submit', function(e) {
    e.preventDefault();
    var month = document.getElementById('month').value;
    fetchData(month);
});

function fetchData(month) {
    $.getJSON('get_data.php?month=' + month, function(data) {
        var tbody = document.getElementById('dataTable').getElementsByTagName('tbody')[0];
        tbody.innerHTML = ''; // Hapus isi tabel sebelumnya
        
        data.forEach(function(row) {
            var tr = document.createElement('tr');
            
            var tdWaktu = document.createElement('td');
            tdWaktu.appendChild(document.createTextNode(row.waktu));
            tr.appendChild(tdWaktu);
            
            var tdTemperature = document.createElement('td');
            tdTemperature.appendChild(document.createTextNode(row.temperature));
            tr.appendChild(tdTemperature);
            
            var tdHumidity = document.createElement('td');
            tdHumidity.appendChild(document.createTextNode(row.humidity));
            tr.appendChild(tdHumidity);
            
            tbody.appendChild(tr);
        });
    });
}

// Load initial data
fetchData(new Date().getMonth() + 1);
</script>

</body>
</html>
