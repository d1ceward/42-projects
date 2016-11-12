<?php
require_once('Vertex.class.php');
class Matrix {
	const IDENTITY = 0, SCALE = 1, RX = 2, RY = 3, RZ = 4, TRANSLATION = 5, PROJECTION = 6;
	private $_matrix;
	public static $verbose = false;
	function __construct(array $kwargs) {
		if ($kwargs["preset"] === self::SCALE) {
			if (array_key_exists("scale", $kwargs))
				$this->_scaleMatrix($kwargs["scale"]);
		}
		else if (array_key_exists("angle", $kwargs) && ($kwargs["preset"] === self::RX || $kwargs["preset"] === self::RY || $kwargs["preset"] === self::RZ )) {
			if ($kwargs["preset"] === self::RX)
				$this->_Rx($kwargs["angle"]);
			if ($kwargs["preset"] === self::RY)
				$this->_Ry($kwargs["angle"]);
			if ($kwargs["preset"] === self::RZ)
				$this->_Rz($kwargs["angle"]);
		}
		else if ($kwargs["preset"] === self::TRANSLATION) {
			if (array_key_exists("vtc", $kwargs))
				$this->_transMatrix($kwargs["vtc"]);
		}
		else if ($kwargs["preset"] === self::PROJECTION && array_key_exists("fov", $kwargs) && array_key_exists("ratio", $kwargs) && array_key_exists("near", $kwargs) && array_key_exists("far", $kwargs))
			$this->_projMatrix($kwargs["fov"], $kwargs["ratio"], $kwargs["near"], $kwargs["far"]);
		else if ($kwargs["preset"] === self::IDENTITY)
			$this->_idMatrix();
	}
	function __destruct() {
		if (self::$verbose)
			print("Matrix instance destructed".PHP_EOL);
	}
	function __toString() {
		$ret = sprintf("M | vtcX | vtcY | vtcZ | vtxO".PHP_EOL);
		$ret .= sprintf("-----------------------------".PHP_EOL);
		$ret .= sprintf("x | %.2f | %.2f | %.2f | %.2f".PHP_EOL, $this->_matrix[0][0], $this->_matrix[0][1], $this->_matrix[0][2], $this->_matrix[0][3]);
		$ret .= sprintf("y | %.2f | %.2f | %.2f | %.2f".PHP_EOL, $this->_matrix[1][0], $this->_matrix[1][1], $this->_matrix[1][2], $this->_matrix[1][3]);
		$ret .= sprintf("z | %.2f | %.2f | %.2f | %.2f".PHP_EOL, $this->_matrix[2][0], $this->_matrix[2][1], $this->_matrix[2][2], $this->_matrix[2][3]);
		$ret .= sprintf("w | %.2f | %.2f | %.2f | %.2f", $this->_matrix[3][0], $this->_matrix[3][1], $this->_matrix[3][2], $this->_matrix[3][3]);
		return $ret;
	}
	public static function doc() {
		return file_get_contents("Color.doc.txt");
	}
	private function _idMatrix() {
		$this->_matrix = array(
			array(1, 0, 0, 0),
			array(0, 1, 0, 0),
			array(0, 0, 1, 0),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix IDENTITY instance constructed".PHP_EOL);
	}
	private function _transMatrix(Vector $translation) {
		$this->_matrix = array(
			array(1, 0, 0, $translation->getX()),
			array(0, 1, 0, $translation->getY()),
			array(0, 0, 1, $translation->getZ()),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix TRANSLATION preset instance constructed".PHP_EOL);
	}
	private function _scaleMatrix($scale) {
		$this->_matrix = array(
			array($scale, 0, 0, 0),
			array(0, $scale, 0, 0),
			array(0, 0, $scale, 0),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix SCALE preset instance constructed".PHP_EOL);
	}
	private function _Rx($angle) {
		$this->_matrix = array(
			array(1, 0, 0, 0),
			array(0, cos($angle), -sin($angle), 0),
			array(0, sin($angle), cos($angle), 0),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix Ox ROTATION preset instance constructed".PHP_EOL);
	}
	private function _Ry($angle) {
		$this->_matrix = array(
			array(cos($angle), 0, sin($angle), 0),
			array(0, 1, 0, 0),
			array(-sin($angle), 0, cos($angle), 0),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix Oy ROTATION preset instance constructed".PHP_EOL);
	}
	private function _Rz($angle) {
		$this->_matrix = array(
			array(cos($angle), -sin($angle), 0, 0),
			array(sin($angle), cos($angle), 0, 0),
			array(0, 0, 1, 0),
			array(0, 0, 0, 1));
		if (self::$verbose)
			print("Matrix Oz ROTATION preset instance constructed".PHP_EOL);
	}
	private function _projMatrix($fov, $ratio, $near, $far) {
		$this->_matrix = array(
			array((1 / tan(deg2rad($fov / 2))) / $ratio, 0, 0, 0),
			array(0, 1 / tan(deg2rad($fov / 2)), 0, 0),
			array(0, 0, -$far * (1 / ($far - $near)), -1 - ($far * $near) * (1 / ($far - $near))),
			array(0, 0, -1, 0));
		if (self::$verbose)
			print("Matrix PROJECTION preset instance constructed".PHP_EOL);
	}
	public function mult(Matrix $rhs) {
		$res = clone $this;
		$i = 0;
		while ($i < 4) {
			$j = 0;
			while ($j < 4) {
				$k = -1;
				$sum = 0;
				while (++$k < 4)
					$sum += $this->_matrix[$i][$k] * $rhs->_matrix[$k][$j];
				$res->_matrix[$i][$j] = $sum;
				$j++;
			}
			$i++;
		}
		return ($res);
	}
	public function transformVertex(Vertex $vtx) {
		return new Vertex(array(
			'x' => ($this->_matrix[0][0] * $vtx->getX() + $this->_matrix[0][1]
				* $vtx->getY() + $this->_matrix[0][2] * $vtx->getZ() + $this->_matrix[0][3] * $vtx->getW()),
			'y' => ($this->_matrix[1][0] * $vtx->getX() + $this->_matrix[1][1]
				* $vtx->getY() + $this->_matrix[1][2] * $vtx->getZ() + $this->_matrix[1][3] * $vtx->getW()),
			'z' => ($this->_matrix[2][0] * $vtx->getX() + $this->_matrix[2][1]
				* $vtx->getY() + $this->_matrix[2][2] * $vtx->getZ() + $this->_matrix[2][3] * $vtx->getW()),
			'w' => ($this->_matrix[3][0] * $vtx->getX() + $this->_matrix[3][1]
				* $vtx->getY() + $this->_matrix[3][2] * $vtx->getZ() + $this->_matrix[3][3] * $vtx->getW()),
			'color' => $vtx->getColor()));
	}
}
?>
