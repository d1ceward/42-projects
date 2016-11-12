<?php
$content = file_get_contents("list.csv");
$lines = explode("\n", $content);
$liness = array();
foreach ($lines as $line) {
	$note = explode(";", $line);
	if ($line != "")
		$liness[$note[0]] = $note[1];
}
echo json_encode($liness);
?>