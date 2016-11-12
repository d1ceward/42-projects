<?php
require_once('Color.class.php');
class Vertex {
	private $_x, $_y, $_z, $_w, $_color;
	public static $verbose = False;
	function __construct(array $kwargs) {
		$this->_x = $kwargs['x'];
		$this->_y = $kwargs['y'];
		$this->_z = $kwargs['z'];
		$this->_w = array_key_exists('w', $kwargs) ? $kwargs['w'] : 1.0;
		$this->_color = array_key_exists('color', $kwargs) ? $this->_color = clone $kwargs['color'] : new Color(array('rgb' => 0xffffff));
		if (self::$verbose)
			printf("Vertex( x: %3.2f, y: %3.2f, z:%3.2f, w:%3.2f, %s ) constructed".PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);
	}
	function __destruct() {
		if (self::$verbose)
			printf("Vertex( x: %3.2f, y: %3.2f, z:%3.2f, w:%3.2f, %s ) destructed".PHP_EOL, $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);
	}
	function __toString() {
		if (self::$verbose)
			return sprintf("Vertex( x: %3.2f, y: %3.2f, z:%3.2f, w:%3.2f, %s )", $this->_x, $this->_y, $this->_z, $this->_w, $this->_color);
		else
			return sprintf("Vertex( x: %3.2f, y: %3.2f, z:%3.2f, w:%3.2f )", $this->_x, $this->_y, $this->_z, $this->_w);
	}
	static function doc() {
		return file_get_contents("Vertex.doc.txt");
	}
	public function setX($x) { $this->_x = $x; }
	public function getX() { return $this->_x; }
	public function setY($y) { $this->_y = $y; }
	public function getY() { return $this->_y; }
	public function setZ($z) { $this->_z = $z; }
	public function getZ() { return $this->_z; }
	public function setW($w) { $this->_w = $w; }
	public function getW() { return $this->_w; }
	public function setColor(Color $color) { $this->_color = $color; }
	public function getColor() { return $this->_color; }
}
?>
