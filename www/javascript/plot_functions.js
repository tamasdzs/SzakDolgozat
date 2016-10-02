var checkInterval = 0.5; 
var filesToCheck = [ "results/s.csv", "results/a.csv" ];
var lastSignal = [];
var lastApr = [];
var lastAprStr = "";

google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(drawChart);

function drawChart( signal, apr, chartName ) {
	
	var toPlot = [];
	
	toPlot.push(['Time', 'Signal', 'Approximation']);
	
	for ( var i = 0; i < signal.length; ++i ) {
		var nextPlot = [ i, parseFloat(signal[i]), parseFloat(apr[i]) ];
		toPlot.push(nextPlot);
	}
	
	var data = google.visualization.arrayToDataTable(toPlot);
	var options = { 
		  title: 'ECG Compression',
          curveType: 'function',
          legend: { position: 'bottom' }
    }
    
    var chart = new google.visualization.LineChart(document.getElementById(chartName));
    
    chart.draw(data, options);

}

function checkResults() {
    
    $.get(filesToCheck[1], function (data) {
		if( data != lastAprStr ) {
			lastApr = data.split('\n');
			lastAprStr = data;
			
			$.get(filesToCheck[0], function (data) {
				lastSignal = data.split('\n');
				console.log(lastSignal);
				drawChart(lastSignal, lastApr, 'in_build_chart');
			});
		} else {
			console.log("results unchanged. Moving on...");
		}
    });
  
    
}

$(document).ready(function () {
    setInterval(checkResults, 1000 * checkInterval);
});

