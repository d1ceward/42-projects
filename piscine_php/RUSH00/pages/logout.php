<?php
if (isset($_SESSION["logged_as_user"]))
	session_destroy();
header("Location: index.php");
?>