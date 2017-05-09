<?php
	
	/* Check if there is already an ongoing animation/compression */
	if ( system("ps -aux | grep main | wc -l") == "2" ) {
		
		$inputPath = "../uploads/".$_POST["resultID"].".cmp";
		$outputPath = "../results/".$_POST["resultID"].".txt";
		/*
		$inputPath = "../uploads/decomp.cmp";
		$outputPath = "../results/decomp.txt";
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
