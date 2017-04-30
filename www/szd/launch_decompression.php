<?php
	
	/* Check if there is already an ongoing animation/compression */
	if ( system("ps -aux | grep main | wc -l") == "2" ) {
		
		$inputPath = "../uploads/".$_POST["resultID"].".cmp";
		$outputPath = "../results/".$_POST["resultID"].".txt";
		
		/* Validate input 
		if ($file = fopen($inputPath, "r")) {
			while(!feof($file)) {
				$line = fgets($file);
				
				$line_arr = explode(" ", $line);
				foreach( $line_arr, $item ) {
					if( !ctype_digit((string)$item) ) {
						echo "error";
						
						/* clean up 
						exec("rm ".$inputPath, $output, $exit_code);
						
						exit();
					}
				}
			}
			fclose($file);
		}
		else 
		{
				echo "fileOpenError";
				exit();
		}
		*/ 

		/* Run main */
		chdir('cpp');
		exec("./main 3 ".$inputPath." ".$outputPath , $output, $exit_code);		
		
		
		/* Clean up */
		exec("rm ".$inputPath, $output, $exit_code);
		echo "success";
		
	}
	else 
	{
		echo "error";
	}		
?>
