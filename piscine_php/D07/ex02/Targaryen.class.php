<?php
class Targaryen {
	function __construct() {
	}
	public function resistsFire() {
		return False;
	}
	public function getBurned() {
		if (!$this->resistsFire())
			return "burns alive";
		else
			return "emerges naked but unharmed";
	}
}
?>
