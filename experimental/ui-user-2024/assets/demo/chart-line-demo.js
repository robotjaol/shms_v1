Chart.defaults.global.defaultFontFamily = '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#292b2c';
const ctx = document.getElementById('myLinechart').getContext('2d');
const data = {
    labels: 
    datasets: [
        {
            label: 'humidity',
            data: [],
            backgroundColor: 'rgba(135,206,250, 0.2)',
            borderColor: 'rgba(100,149,237, 1)',
            borderWidth: 1
        },
        {
            label: 'temperature',
            data: [],
            backgroundColor: 'rgba(144,238,144, 0.2)',
            borderColor: 'rgba(34,139,34, 1)',
            borderWidth: 1
        }
        
    ]
};

const myChart = new Chart(ctx, {
    type: 'line',
    data: data,
    options: {
    }
});
