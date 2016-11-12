<?php
class UnholyFactory {
	private $products;
	function __construct() {
		$this->products = array();
	}
	public function absorb($fighter) {
		if (is_a($fighter, "Fighter")) {
			if (!array_key_exists($fighter->getType(), $this->products)) {
				print("(Factory absorbed a fighter of type ".$fighter->getType().")".PHP_EOL);
				$this->products[$fighter->getType()] = $fighter;
			} else
				print("(Factory already absorbed a fighter of type ".$fighter->getType().")".PHP_EOL);
		} else
			print("(Factory can't absorb this, it's not a fighter)".PHP_EOL);
	}
	public function fabricate($x) {
		if (!array_key_exists($x, $this->products)) {
			print("(Factory hasn't absorbed any fighter of type ".$x.")".PHP_EOL);
			return null;
		} else {
			print("(Factory fabricates a fighter of type ".$x.")".PHP_EOL);
			return clone $this->products[$x];
		}
	}
}
?>
