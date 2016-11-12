<?php
abstract class Lannister {
	public function sleepWith($b) {
		if (is_a($b, "Lannister"))
			print("Not even if I'm drunk !".PHP_EOL);
		else if (is_a($b, "Stark"))
			print("Let's do this.".PHP_EOL);
	}
}
?>
