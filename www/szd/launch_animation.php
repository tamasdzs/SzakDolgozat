<?php

	    /* Check if there is already an ongoing animation */
		
		
		if ( system("ps -aux | grep main | wc -l") == "2" ) {
		
			/* Clean results dir */
			$animation_path = getcwd();
			chdir('server_scripts');
			exec("./clean_results.sh", $output, $exit_code);
			chdir($animation_path);
			
			if ( $exit_code == 0 ) {
				
				/* If cleanup was OK, then start example compression */
				chdir('cpp');
				exec("./main 1", $output, $exit_code);
				
			}
			else {
				exit($exit_code);
			}
			
			
			$_SESSION['isAnimating'] = "";
			exit($exit_code);
		} 
		else 
		{
			echo system("ps -aux | grep main | wc -l");
		}
	
?>
