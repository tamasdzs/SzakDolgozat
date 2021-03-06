var checkInterval = 0.5; 

var filesToCheck = [ "results/in_action/s.csv", "results/in_action/a.csv", 
					 "results/qrs/s.csv", "results/qrs/a.csv",
					 "results/t/s.csv", "results/t/a.csv",
					 "results/p/s.csv", "results/p/a.csv",
					 "results/combined/s.csv", "results/combined/a.csv"];

var lastAprStr = "EMPTY\n";
var lastQRS = "EMPTY\n";
var lastP = "EMPTY\n";
var lastT = "EMPTY\n";
var intervalIDs = [];
var isCompressing;

var prevDatas = ["EMPTY\n", "EMPTY\n", "EMPTY\n"];
var filesToCheck_results = ["results/prd/prd.txt", "results/qs/qs.txt", "results/cr/cr.txt"];

google.charts.load('current', {'packages':['corechart']});
google.charts.setOnLoadCallback(drawChart);

function drawChart( functions, chartName, chartDesc, functionLabels) {
	
	var toPlot = [];
	
	var numOfPlots = functions.length;
	
	toPlot.push(functionLabels);
	
	for ( var i = 0; i < functions[0].length; ++i ) {
		var nextPlot = [];
		nextPlot.push(i);
		for ( var j = 0; j < numOfPlots; ++j ) {
			nextPlot.push(parseFloat(functions[j][i]));
		}
		toPlot.push(nextPlot);
	}
	
	var data = google.visualization.arrayToDataTable(toPlot);
	var options = { 
		  title: chartDesc,
          curveType: 'function',
          legend: { position: 'bottom' }
    }
    
    var chart = new google.visualization.LineChart(document.getElementById(chartName));
    
    chart.draw(data, options);
}

function getResultsAndDraw(sigLocation, aprLocation, lastData, toClear, toClearPos, chartName, chartTitle, legend) {
	$.get(aprLocation, function (data) {
		if( data != lastData) {
			var apr = data.split('\n');
			var sig = [];
			lastData = data;
			
			$.get(sigLocation, function (data) {
				sig = data.split('\n');
				drawChart([sig, apr], chartName, chartTitle, legend);
			});
			if ( toClear != "noClear" ) {
				clearInterval(toClear[toClearPos]);
				if ( chartName == 'P_chart' ) {
					clearInterval(toClear[0]);
					drawAggregatedApr();
				}
			}
		} else {
			
		}
	});
}

function drawAggregatedApr() {
	
	var chartName = 'in_build_chart';
	var chartTitle = "Aggregated approximations";
	var toPlot = [];
	var legends = ['Time', 'Original', 'QRS', 'T', 'P'];
	
	$.ajax({
		async: false,
		type: 'GET',
		url: filesToCheck[2],
		success: function(data) {
          toPlot.push(data.split('\n'));
		}
	});
	
	for ( var currApr = 3; currApr < filesToCheck.length - 2; currApr+=2 ) {
		$.ajax({
			async: false,
			type: 'GET',
			url: filesToCheck[currApr],
			success: function(data) {
				toPlot.push(data.split('\n'));
			}
		});
	}
	
	drawChart(toPlot, chartName, chartTitle, legends);
}

function getResultsAndPublish(prdLocation, qsLocation, crLocation, prevDatas) {
	
	$.get(prdLocation, function (data) {
		if( data != prevDatas[0]) {
			prevDatas[0] = data;
			document.getElementById("prd").innerHTML = "PRD = " + data.toString();
		}
	});
	
	$.get(qsLocation, function (data) {
		if( data != prevDatas[1]) {
			prevDatas[1] = data;
			document.getElementById("qs").innerHTML = "QS  = " + data.toString();
		}
	});
	
	$.get(crLocation, function (data) {
		if( data != prevDatas[2]) {
			prevDatas[2] = data;
			document.getElementById("cr").innerHTML = "CR  = " + data.toString();
		}
	});
}

$(document).ready(function () {
	isCompressing = true;
    
    intervalIDs.push(setInterval(function() { getResultsAndDraw(filesToCheck[0], filesToCheck[1], lastAprStr, "noClear", 0, 'in_build_chart', 'ECG Compression', ['Time', 'Signal', 'Approximation']); } , 200* checkInterval));
    intervalIDs.push(setInterval(function() { getResultsAndDraw(filesToCheck[2], filesToCheck[3], lastQRS, intervalIDs, 1, 'QRS_chart', 'Approximation of QRS', ['Time', 'Signal', 'QRS']); } , 200 * checkInterval));
    intervalIDs.push(setInterval(function() { getResultsAndDraw(filesToCheck[4], filesToCheck[5], lastT, intervalIDs, 2, 'T_chart', 'Approximation of T segment', ['Time', 'Signal','T']); }, 200 * checkInterval));
    intervalIDs.push(setInterval(function() { getResultsAndDraw(filesToCheck[6], filesToCheck[7], lastP, intervalIDs, 3, 'P_chart', 'Approximation of P segment', ['Time', 'Signal','P']); }, 200 * checkInterval));
    intervalIDs.push(setInterval(function() { getResultsAndPublish(filesToCheck_results[0], filesToCheck_results[1], filesToCheck_results[2], prevDatas); }, 200 * checkInterval));
    
});

