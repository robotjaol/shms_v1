<!DOCTYPE html>
<html>
<head>
    <title>Highcharts Chart</title>
    <script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>
    <script src="https://code.highcharts.com/highcharts.js"></script>
    <script src="https://code.highcharts.com/modules/series-label.js"></script>
    <script src="https://code.highcharts.com/modules/exporting.js"></script>
    <script src="https://code.highcharts.com/modules/export-data.js"></script>
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

<div id="container" style="width:100%; height:400px;"></div>

<script>
document.getElementById('monthForm').addEventListener('submit', function(e) {
    e.preventDefault();
    var month = document.getElementById('month').value;
    fetchData(month);
});

function fetchData(month) {
    $.getJSON('get_data.php?month=' + month, function(data) {
        var categories = data.map(function(e) {
            return e.waktu;
        });
        var temperatures = data.map(function(e) {
            return parseFloat(e.temperature);
        });
        var humidity = data.map(function(e) {
            return parseFloat(e.humidity);
        });

        Highcharts.chart('container', {
            title: {
                text: 'Temperature and Humidity Data'
            },
            xAxis: {
                categories: categories
            },
            yAxis: {
                title: {
                    text: 'Values'
                }
            },
            series: [{
                name: 'Temperature',
                data: temperatures
            }, {
                name: 'Humidity',
                data: humidity
            }]
        });
    });
}

// Load initial data
fetchData(new Date().getMonth() + 1);
</script>

</body>
</html>