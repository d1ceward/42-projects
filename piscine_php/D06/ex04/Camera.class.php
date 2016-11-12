<?php
require_once('Matrix.class.php');
class Camera {
	private $_origin, $_height, $_width, $_far, $_near, $_tT, $_tR;
	public static $verbose = FALSE;
	function __construct(array $kwargs) {
		if (!array_key_exists('origin', $kwargs) || !array_key_exists('orientation', $kwargs) || !array_key_exists('fov', $kwargs) || !array_key_exists('near', $kwargs) || !array_key_exists('far', $kwargs) || ((!array_key_exists('width', $kwargs) || !array_key_exists('height', $kwargs)) && !array_key_exists('ratio', $kwargs)))
			return ;
		if (array_key_exists('ratio', $kwargs)) {
			$kwargs['width'] = $kwargs['ratio'] * 480;
			$kwargs['height'] = 480;
		} else
			$kwargs['ratio'] = $kwargs['width'] / $kwargs['height'];
		$this->_height = $kwargs['height'];
		$this->_width = $kwargs['width'];
		$this->_origin = $kwargs['origin'];
		$this->_near = $kwargs['near'];
		$this->_far = $kwargs['far'];
		$this->_tT = $this->_create_tT();
		$this->_tR = NULL;
		if (self::$verbose)
			print("Camera instance constructed".PHP_EOL);
	}
	function __destruct() {
		if (self::$verbose)
			print("Camera instance destructed".PHP_EOL);
	}
	function __toString() {
		return sprintf("Camera( ".PHP_EOL."+Origine: ". $this->_origin.PHP_EOL."+ tT:".PHP_EOL.$this->_tT.PHP_EOL."+tR:".PHP_EOL.$this->tR);
	}
	public static function doc() {
		return file_get_contents("Camera.doc.txt");
	}
	private function _create_tT() {
		$translation = new Vector(array( 'dest' => $this->_origin));
		$opposite = $translation->opposite();
		$tT = new Matrix(array('preset' => Matrix::TRANSLATION, 'vtc' => $opposite));
		return $tT;
	}
}
?>
