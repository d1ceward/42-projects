<?php
if (isset($_GET['id']) && is_numeric($_GET['id'])) {
	$content = file_get_contents("list.csv");
	$lines = explode("\n", $content);
	$result = "";
	foreach ($lines as $line) {
		$liner = explode(";", $line);
		if ($liner[0] != $_GET['id'] && $line != "")
			$result = $result.$line."\n";
	}
	file_put_contents("list.csv", $result);
}
?>