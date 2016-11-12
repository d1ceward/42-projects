<?php
require_once '../../config/config.php';
if (isset($_SESSION['data']))
	session_destroy();
?>