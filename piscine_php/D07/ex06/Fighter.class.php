<?php
abstract class Fighter {
	private $type;
	function __construct($type) {
		$this->type = $type;
	}
	abstract function fight($target);
	public function getType() {
		return $this->type;
	}
}
?>
