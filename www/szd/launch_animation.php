<?php

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
	
	exit($exit_code);
	
?>
