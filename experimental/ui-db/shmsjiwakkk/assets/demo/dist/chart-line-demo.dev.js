"use strict";

// Set new default font family and font color to mimic Bootstrap's default styling
Chart.defaults.global.defaultFontFamily = '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#292b2c'; // Get the context of the canvas element we want to select

var ctx = document.getElementById('myLinechart').getContext('2d'); // Define the data for the chart

var data = {
  labels: ['cok', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December', 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December', 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December', 'January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December'],
  datasets: [{
    label: 'kelembaban',
    data: [30, 25, 35, 40, 45, 30, 20, 25, 30, 20, 25, 30, 35, 40, 45, 30, 20, 25, 30, 20, 25, 30, 35, 40, 45, 50, 30, 25, 35, 40, 45, 50, 30, 20, 25, 30, 35, 40, 45, 30, 20, 25, 30, 20, 25, 30, 35, 40, 45, 50, 30, 25],
    backgroundColor: 'rgba(135,206,250, 0.2)',
    borderColor: 'rgba(100,149,237, 1)',
    borderWidth: 1
  }, {
    label: 'suhu',
    data: [90, 43, 42, 45, 44, 38, 36, 27, 38, 25, 43, 42, 45, 44, 38, 36, 27, 38, 25, 43, 42, 45, 44, 38, 36, 59, 25, 43, 42, 45, 44, 38, 36, 27, 38, 25, 43, 42, 45, 44, 38, 36, 27, 38, 25, 43, 42, 45, 44, 38, 36, 100],
    backgroundColor: 'rgba(144,238,144, 0.2)',
    borderColor: 'rgba(34,139,34, 1)',
    borderWidth: 1
  }]
}; // Create a new Chart instance

var myChart = new Chart(ctx, {
  type: 'line',
  data: data,
  options: {// Add other chart options here (e.g., title, scales, animations)
  }
});
//# sourceMappingURL=chart-line-demo.dev.js.map
