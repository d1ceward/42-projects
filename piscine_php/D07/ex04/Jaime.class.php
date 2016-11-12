<?php
class Jaime extends Lannister {
	public function sleepWith($b) {
		if (is_a($b, "Cersei"))
			print("With pleasure, but only in a tower in Winterfell, then.".PHP_EOL);
		else
			parent::sleepWith($b);
	}
}
?>
