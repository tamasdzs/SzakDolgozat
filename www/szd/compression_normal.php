<!DOCTYPE html>
<html>

<head>
	<link rel="stylesheet" href="./css/compression_normal.css">
</head>

<body>

<div id="whiteTop">

 <ul>
  <li id="titleLi">             <img id="CimMenu" src="./resources/images/Cim.png" alt="Ekg Jelek Tömörítése" > </li>
  <li class="regularNavPoint"> <a href="about.php">  <img id="IsmMenu" src="./resources/images/Ism_Alap.png" alt="Ismerteto" onmouseover="hoverChangeImg(this, './resources/images/Ism_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Ism_Alap.png')" > </a>   </li>
  <li class="regularNavPoint"> <a href="compression_normal.php"> <img id="TomMenu" src="./resources/images/Tom_Kijelolt.png" alt="Tömörítés" onmouseover="hoverChangeImg(this, './resources/images/Tom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Tom_Kijelolt.png')">    </a>      </li>
  <li class="regularNavPoint"> <a href="decompression_normal.php"> <img id="KitomMenu" src="./resources/images/Kitom_Alap.png" alt="Kitömörítés" onmouseover="hoverChangeImg(this, './resources/images/Kitom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Kitom_Alap.png')"> </a> </li>
  <li id="finalLi">   <a href="animation.php">  <img id="AnimMenu" src="./resources/images/Anim_Alap.png" alt="Animáció" onmouseover="hoverChangeImg(this, './resources/images/Anim_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Anim_Alap.png')">  </a> </li>
</ul> 

</div>

<table id="graphHolder">
	
	<tr>
		<td  class="blueCell" id="00" onclick="showRecords()">
			<img id="Recbutton" src="./resources/images/jelek.png" alt="Records">
		</td>
		<td class="redCell" id="01" onclick="hideRecords('01')" >
			<img class="recImage" id="01_img" src="" >
		</td>
		<td class="redCell" id="02" onclick="hideRecords('02')">
			<img class="recImage" id="02_img" src="" >
		</td>
		<td class="redCell" id="03" onclick="hideRecords('03')">
			<img class="recImage" id="03_img" src="" >
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="10" onclick="hideRecords('10')">
			<img class="recImage" id="10_img" src="" >
		</td>
		<td  class="redCell" id="11" onclick="hideRecords('11')">
			<img class="recImage" id="11_img" src="" >
		</td>
		<td  class="redCell" id="12" onclick="hideRecords('12')">
			<img class="recImage" id="12_img" src="" >
		</td>
		<td  class="redCell" id="13" onclick="hideRecords('13')">
			<img class="recImage" id="13_img" src="" >
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="20" onclick="hideRecords('20')">
			<img class="recImage" id="20_img" src="" >
		</td>
		<td  class="redCell" id="21" onclick="hideRecords('21')">
			<img class="recImage" id="21_img" src="" >
		</td>
		<td  class="redCell" id="22" onclick="hideRecords('22')">
			<img class="recImage" id="22_img" src="" >
		</td>
		<td  class="blueCell" id="23" onclick="beginCompression()">
			<img id="Enterbutton" src="./resources/images/tomorites.png" >
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="30" onclick="hideRecords('30')">
			<img class="recImage" id="30_img" src="" >
		</td>
		<td  class="redCell" id="31" onclick="hideRecords('31')">
			<img class="recImage" id="31_img" src="" >
		</td>
		<td  class="redCell" id="32" onclick="hideRecords('32')">
			<img class="recImage" id="32_img" src="" >
		</td>
		<td  class="noBorderCell" id="33">
			
		</td>
	</tr>
	
	
</table>

<footer id="pageFooter">
	<img id="pageFooterImage" src="./resources/images/FOOTER.png" alt="tamasdzs@gmail.com" >
</footer>

<script>
	
	isShowingSigs = false;
	
	function hoverChangeImg(obj, path) {
		obj.src = path;
	}
	
	function inArray(array, key) {
		ret = -1;
		for(var i = 0; ( i < array.length ) && ( ret == -1 ); ++i ) {
			if ( key == array[i] ) {
				ret = i;
			}
		}
		return ret;
	}
	
	function hideRecords( selectedSig ) {
		for ( var i = 0; i < 4; ++i ) {
			for ( var j = 0; j < 4; ++j ) {
				
				var coord = i.toString() + j.toString();
				if ( ( coord != "00" ) && 
				     ( coord != "23" ) &&
				     ( coord != "33" ) && 
				     ( coord != selectedSig ) ) {
						 
					if ( coord == selectedSig) {
						isShowingSigs = true;
						//sigId = document.getElementById(coord+"_img").alt;
					}
					
					document.getElementById(coord).className = "redCell";	 
					//document.getElementById(coord).innerHTML = "";
					document.getElementById(coord+"_img").style.display = 'none';
				}
			}
		}
	}
	
	function showRecords() {
		
		if ( isShowingSigs == false ) {
			
			isShowingSigs = true;
			
			var recordNames     = ['117', '118', '119', '201', '103'];
			var availableCoords = ['01', '02', '03', '10', '11', '12', '13', '20', '21', '22', '30', '31', '32'];
			
			var N = recordNames.length;
			
			var idx = -1;
			
			for ( var i = 0; i <  N; ++i ) {
				
				while( idx == -1 ) {
					coord1 = Math.floor((Math.random() * 4) ); 
					coord2 = Math.floor((Math.random() * 4) );
				
					strCoord = coord1.toString() + coord2.toString();
					idx = inArray(availableCoords, strCoord);
					
					if ( idx != -1 ) {
						document.getElementById(availableCoords[idx]).className = "blueCell";
						document.getElementById(availableCoords[idx].toString() +"_img").alt = recordNames[i];
						document.getElementById(availableCoords[idx].toString() +"_img").src = "./resources/images/"+recordNames[i].toString()+"_2.png";
						document.getElementById(availableCoords[idx].toString() +"_img").style.display = 'block';
						availableCoords.splice(idx, 1);
					}
				}
				idx = -1;
			}		
		}
		else {
			isShowingSigs = false;
			hideRecords("00");
		}
	}
	
	function beginCompression() {
		
		if ( isShowingSigs == false ) {
			document.getElementById("33").innerHTML = "Valasszon tomoritendo merest";
			document.getElementById("00").className = "blueCell";
			return;
		}
		
		var numOfBlueCells = 0;
		var idx = "";
		
		for ( var i = 0; i < 4; ++i ) {
			for ( var j = 0; j < 4; ++j ) {
					
				var coord = i.toString() + j.toString();	
					
				if ( ( coord != "00" ) && 
				 ( coord != "23" ) &&
				 ( coord != "33" ) &&  
				 ( document.getElementById(coord).className == "blueCell" )) {
				 
					numOfBlueCells++;
					idx = coord;
				}
			}
		}
		
		if ( numOfBlueCells != 1 ){
			document.getElementById("33").innerHTML = "Valasszon tomoritendo merest";
			document.getElementById("00").className = "blueCell";
			return;
		}
		else 
		{
			document.getElementById("33").innerHTML = "";
			//signalId = document.getElementById(idx).innerHTML; 
			signalId = document.getElementById(idx+"_img").alt;
			window.location.href = "compression_loading.php?sigID=" + signalId; //use $_GET['sigID'] in compression_loading.php
		}
	}
	
</script>

</body>
</html> 
