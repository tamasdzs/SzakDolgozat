<?php
	
	/* Check if there is already an ongoing animation/compression */
	if ( system("ps -aux | grep main | wc -l") == "2" ) {
	
		if ( file_exists("/var/www/html/szakdolgozat/results/".$_POST["sigID"].".cmp") ) {
			echo "success";
			exit();
		}
		
		chdir('cpp');
		exec("./main 2 signals/".$_POST["sigID"]."/".$_POST["sigID"]." /var/www/html/szakdolgozat/results/".$_POST["sigID"].".cmp" , $output, $exit_code);		
		echo "success";
	}
	else 
	{
		echo "compression_ongoing";
	}		
?>
