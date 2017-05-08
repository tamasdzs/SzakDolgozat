<!DOCTYPE html>
<html>

<head>
	<link rel="stylesheet" href="./css/decompression_loading.css">
	<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
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

<div id="Main">
	<img id="mainImage" src="">
</div>

<?php

$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]);
$uploadOk = 1;
$FileType = pathinfo($target_file,PATHINFO_EXTENSION);


// Check if file already exists
if (file_exists($target_file)) {
    echo "<script>alert(\"File already exists\");</script>";
    $uploadOk = 0;
}
// Check file size
if ($_FILES["fileToUpload"]["size"] > 500000) {
    echo "<script>alert(\"File is too large\");</script>";
    $uploadOk = 0;
}
// Allow certain file formats
if($FileType != "cmp" ) {
    echo "<script>alert(\"only .cmp allowed, not " . $FileType. "\")</script>";
    $uploadOk = 0;
}

$validIds = array("101", "117", "118", "119", "201", "213", "103");
$resultId = str_replace( ".cmp", "", basename($_FILES["fileToUpload"]["name"]) );

if ( in_array($resultId, $validIds) ) {
	
}
else {
	$uploadOk = 0;
}	

// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
    echo "<script>alert(\"File upload failed\");</script>";
// if everything is ok, try to upload file
} else {
    if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
        
        //$resultId = str_replace( ".cmp", "", basename($_FILES["fileToUpload"]["name"]) );
        
        echo '<script>
			  document.getElementById("mainImage").src = "./resources/images/Loading_Icon.gif";
			  $.ajax({
                type: "POST",
                url: "launch_decompression.php",
                data: { resultID: '. $resultId .' },
                success: function(data) {
					if ( data.includes("success") ) {
						createLinkForDownload("results/'.$resultId.'.txt");
					}
					else {
						alert("Ooops... something went wrong.");
					}
                  }
			   });
			  </script>';
        
        
    } else {
        echo "<script>alert(\"A feltöltés sikertelen :(\");</script>";
    }
}
?>

<footer id="pageFooter">
	<img id="pageFooterImage" src="./resources/images/FOOTER.png" alt="tamasdzs@gmail.com" >
</footer>

<script>
	
	function createLinkForDownload(res_url) {
		document.getElementById("Main").innerHTML = "<a href= \""+res_url+"\" download><img id=\"mainImage\" src=\"./resources/images/Letolto_Uzenet.png\"></a>";
	}
	
	function hoverChangeImg(obj, path) {
		obj.src = path;
	}
	
</script>

</body>
</html> 
