<!DOCTYPE html>
<html>

<head>
	<link rel="stylesheet" href="./css/decompression_normal.css">
</head>

<body>

<div id="whiteTop">

 <ul>
  <li id="titleLi">             <img id="CimMenu" src="./resources/images/Cim.png" alt="Ekg Jelek Tömörítése" > </li>
  <li class="regularNavPoint"> <a href="about.php">  <img id="IsmMenu" src="./resources/images/Ism_Alap.png" alt="Ismerteto" onmouseover="hoverChangeImg(this, './resources/images/Ism_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Ism_Alap.png')" > </a>   </li>
  <li class="regularNavPoint"> <a href="compression_normal.php"> <img id="TomMenu" src="./resources/images/Tom_Alap.png" alt="Tömörítés" onmouseover="hoverChangeImg(this, './resources/images/Tom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Tom_Alap.png')">    </a>      </li>
  <li class="regularNavPoint"> <a href="decompression_normal.php"> <img id="KitomMenu" src="./resources/images/Kitom_Kijelolt.png" alt="Kitömörítés" onmouseover="hoverChangeImg(this, './resources/images/Kitom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Kitom_Kijelolt.png')"> </a> </li>
  <li id="finalLi">   <a href="animation.php">  <img id="AnimMenu" src="./resources/images/Anim_Alap.png" alt="Animáció" onmouseover="hoverChangeImg(this, './resources/images/Anim_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Anim_Alap.png')">  </a> </li>
</ul> 

</div>

<table id="graphHolder">
	
	<tr>
		<td  class="blueCell" id="00">
			<form action="decompression_loading.php" method="post" enctype="multipart/form-data">
				<input type="file" id="fileToUpload" name="fileToUpload" class="hidden" accept=".cmp" >
				<input type="submit" name="fileSubmit" value="upload" id="submitButton" class="hidden">  
			</form>
			<label for="fileToUpload">Browse</label>
		</td>
		<td class="redCell" id="01" >
		
		</td>
		<td class="redCell" id="02" >
		
		</td>
		<td class="redCell" id="03" >
		
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="10">
		
		</td>
		<td  class="redCell" id="11">
		
		</td>
		<td  class="redCell" id="12">
		
		</td>
		<td  class="redCell" id="13">
		
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="20">
		
		</td>
		<td  class="redCell" id="21">
		
		</td>
		<td  class="redCell" id="22">
		
		</td>
		<td  class="blueCell" id="23">
			<label for="submitButton">Upload</label>
		</td>
	</tr>
	<tr>
		<td  class="redCell" id="30">
		
		</td>
		<td  class="redCell" id="31">
		
		</td>
		<td  class="redCell" id="32">
		
		</td>
		<td  class="noBorderCell" id="33">
		
		</td>
	</tr>
	
	
</table>

<footer id="pageFooter">
	<img id="pageFooterImage" src="./resources/images/FOOTER.png" alt="tamasdzs@gmail.com" >
</footer>

<script>
	
	function hoverChangeImg(obj, path) {
		obj.src = path;
	}
	
</script>

</body>
</html> 
