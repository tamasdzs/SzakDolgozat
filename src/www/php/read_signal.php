<?php
	$file_name = $argv[1];
	$fh = fopen($file_name, "r") or die("Could not open " . $file_name);
	echo fread($fh, filesize($file_name));
	fclose($fh);
?>
