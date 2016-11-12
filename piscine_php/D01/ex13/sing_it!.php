#!/usr/bin/php
<?php
if ($argc > 1) {
	if (strcmp($argv[1], "mais pourquoi cette demo ?") === 0) {
		echo "Tout simplement pour qu'en feuilletant le sujet\non ne s'apercoive pas de la nature de l'exo\n";
	} else if (strcmp($argv[1], "mais pourquoi cette chanson ?") === 0) {
		echo "Parce que Kwame a des enfants\n";
	} else if (strcmp($argv[1], "vraiment ?") === 0 && !file_exists(".ouivraiment")) {
		echo "Nan c'est parce que c'est le premier avril\n";
		$handle = fopen(".ouivraiment", "w");
		fclose($handle);
	} else if (strcmp($argv[1], "vraiment ?") === 0 && file_exists(".ouivraiment")) {
		echo "Oui il a vraiment des enfants\n";
		unlink(".ouivraiment");
	}
}
?>