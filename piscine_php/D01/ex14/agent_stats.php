#!/usr/bin/php
<?php
Class User {
	var $username;
	var $nb_mark;
	var $total_mark;
	var $nb_mark_peers;
	var $total_mark_peers;
	var $nb_mark_mouli;
	var $total_mark_mouli;
	function __construct() {
		$this->username = "";
		$this->nb_mark = 0;
		$this->total_mark = 0;
		$this->nb_mark_peers = 0;
		$this->total_mark_peers = 0;
		$this->nb_mark_mouli = 0;
		$this->total_mark_mouli = 0;
	}
}

if ($argc > 1) {
	$nb_mark_peers = 0;
	$total_mark_peers = 0;
	$users = array();
	$str = fgets(STDIN);
	while (($str = fgets(STDIN))) {
		$str = substr($str, 0, -1);
		$values = explode(";", $str);
		if (!array_key_exists($values[0], $users)) {
			$users[$values[0]] = new User();
			$users[$values[0]]->username = $values[0];
		}
		if (is_numeric($values[1])) {
			$users[$values[0]]->nb_mark++;
			$users[$values[0]]->total_mark += $values[1];
			if (strcmp($values[2], "moulinette") === 0) {
				$users[$values[0]]->nb_mark_mouli++;
				$users[$values[0]]->total_mark_mouli += $values[1];
			} else {
				$users[$values[0]]->nb_mark_peers++;
				$users[$values[0]]->total_mark_peers += $values[1];
				$nb_mark_peers++;
				$total_mark_peers += $values[1];
			}
		}
	}
	if (strcmp($argv[1], "moyenne") === 0) {
		echo $total_mark_peers / $nb_mark_peers."\n";
	} else if (strcmp($argv[1], "moyenne_user") === 0) {
		ksort($users);
		foreach ($users as $user) {
			if ($user->nb_mark_peers > 0) {
				if ($user->nb_mark != 0) {
					$average = $user->total_mark_peers / $user->nb_mark_peers;
				} else {
					$average = 0;
				}
				echo $user->username.":".$average."\n";
			}
		}
	} else if (strcmp($argv[1], "ecart_moulinette") === 0) {
		ksort($users);
		foreach ($users as $user) {
			if ($user->nb_mark_mouli > 0 && $user->nb_mark_peers > 0) {
				if ($user->nb_mark_peers != 0 && $user->nb_mark_mouli != 0) {
					$average_mouli = $user->total_mark_mouli / $user->nb_mark_mouli;
					$average_peers = $user->total_mark_peers / $user->nb_mark_peers;
					$diff = $average_peers - $average_mouli;
				} else {
					$diff = 0;
				}
				echo $user->username.":".$diff."\n";
			}
		}
	}
}
?>