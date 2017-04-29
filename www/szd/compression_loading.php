<!DOCTYPE html>
<html>

<head>
	<link rel="stylesheet" href="./css/compression_loading.css">
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

<div id="Main">
	<a id="resLink" href="">
	<img id="mainImage" src="">
	</a>
</div>

<?php
	
	$validIds = array("101", "117", "118", "119", "201", "213");
	$sigId = $_GET['sigID'];
	
	if ( in_array($sigId, $validIds) ) {
		echo '<script>
			  document.getElementById("mainImage").src = "./resources/images/Loading_Icon.gif";
			  </script>';
			  
			  // Run clean_up.sh
			  
			  //Launch compression in compression mode
			  
			  //check that all went well
			  
			  //change image to DONE and add link for download results.
	}
	else {
		
		//replace cat image with whatever Tami gives u
		
		echo '<script>
			  document.getElementById("mainImage").src = "./resources/images/nope.jpg";
			  </script>';
	}
?>

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
