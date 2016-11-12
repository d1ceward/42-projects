#!/usr/bin/php
<?php
	date_default_timezone_set('Europe/Paris');

	$file = fopen("/var/run/utmpx", "r");
	while ($binary = fread($file, 628))
	{
		$unpack = unpack("a256user/a4id/a32line/ipid/itype/I2time/a256host/i16pad", $binary);
		if ($unpack["type"] == 7)
			$user[$unpack["line"]] = array("user" => $unpack["user"], "time" => $unpack["time1"]);
	}
	ksort($user);
	foreach($user as $line => $data)
		printf("% -7s  % -7s  %s \n", $data["user"], $line, date("M j H:i", $data["time"]));
?>
