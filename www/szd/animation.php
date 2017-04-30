<!DOCTYPE html>
<html>

<head>
	<link rel="stylesheet" href="./css/animation.css">
	<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
	<script type="text/javascript" src="http://code.jquery.com/jquery-1.7.1.min.js"></script>
	<script src="./javascript/plot_functions.js"></script>
</head>

<body>

 <ul>
  <li id="titleLi">             <img id="CimMenu" src="./resources/images/Cim.png" alt="Ekg Jelek Tömörítése" > </li>
  <li class="regularNavPoint"> <a href="about.php">  <img id="IsmMenu" src="./resources/images/Ism_Alap.png" alt="Ismerteto" onmouseover="hoverChangeImg(this, './resources/images/Ism_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Ism_Alap.png')" > </a>   </li>
  <li class="regularNavPoint"> <a href="compression_normal.php"> <img id="TomMenu" src="./resources/images/Tom_Alap.png" alt="Tömörítés" onmouseover="hoverChangeImg(this, './resources/images/Tom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Tom_Alap.png')">    </a>      </li>
  <li class="regularNavPoint"> <a href="decompression_normal.php"> <img id="KitomMenu" src="./resources/images/Kitom_Alap.png" alt="Kitömörítés" onmouseover="hoverChangeImg(this, './resources/images/Kitom_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Kitom_Alap.png')"> </a> </li>
  <li id="finalLi">   <a href="animation.php">  <img id="AnimMenu" src="./resources/images/Anim_Kijelolt.png" alt="Animáció" onmouseover="hoverChangeImg(this, './resources/images/Anim_Hover.png')" onmouseout="hoverChangeImg(this, './resources/images/Anim_Kijelolt.png')">  </a> </li>
</ul> 

<table id="graphHolder">
	<caption id="graphHolderCaption"> <img id="graphHolderCaptionImage" src="./resources/images/Felirat.png" alt="Példa tömörítés" > </caption>
	<tr>
		<td rowspan="2" class="graphCell" id="in_build_chart" onclick="launch_animation()">
		
		</td>
		<td class="graphCell" id="QRS_chart">
		
		</td>
		<td class="graphCell" id="T_chart">
		
		</td>
	</tr>
	<tr>
		<td class="graphCell" id="P_chart">
		
		</td>
		<td class="dataCell" id="dataCell">
			<div id="prd">
			</div>
			<div id="qs">
			</div>
			<div id="cr">
			</div>
		</td>
	</tr>
</table>


<script language="javascript" type="text/javascript">
function launch_animation()
{
    $.ajax(
        {
               type: "POST",
               url: "launch_animation.php",
               cache: false,

               success: function(response)
               {
		
               }
         });
}
</script>

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
