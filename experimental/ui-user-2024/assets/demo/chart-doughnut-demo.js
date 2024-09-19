// Set new default font family and font color to mimic Bootstrap's default styling
Chart.defaults.global.defaultFontFamily = '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#292b2c';

// Pie Chart Example



const ctx = document.getElementById('myDoughnutchart').getContext('2d');

const data = {
    labels: ['Humidity', 'Temperature', 'Tilt'],
    datasets: [{
        label: 'My Doughnut Chart',
        data: [30, 50, 20],
        backgroundColor: ['#68AECC', '#DAA5A5', '#F7ECCF'],
        hoverBackgroundColor: ['#559BB8', '#C38686', '#D9CCAA'],
    }]
};

const myDoughnutchart = new Chart(ctx, {
    type: 'doughnut',
    data: data,

});

