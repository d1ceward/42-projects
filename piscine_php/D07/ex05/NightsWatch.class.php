<?php
class NightsWatch {
	private $fighters;
	function __construct() {
		$this->fighters = array();
	}
	public function recruit($soldier) {
		if ($soldier instanceof IFighter)
			$this->fighters[] = $soldier;
	}
	public function fight() {
		foreach($this->fighters as $fighter) {
			$fighter->fight();
		}
	}
}
?>