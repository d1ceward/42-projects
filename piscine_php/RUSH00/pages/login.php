<?php
if (isset($_SESSION["logged_as_user"]))
	header("Location: index.php?page=404");
else {
	$login = ft_secure(@$_POST['login']);
	$pwd = ft_secure(@$_POST['password']);
	if ($login == "")
		$error_msg = "Veuillez indiquer votre identifiant";
	else if ($pwd== "")
		$error_msg  = "Veuillez indiquer votre mot de passe";
	else if (mysqli_num_rows(mysqli_query($db, "SELECT id FROM users WHERE login = '".$login."' AND password = '".crypt_pwd($pwd)."' LIMIT 1")) < 1)
		$error_msg  = "Identifiant ou mot de passe incorrect";
	else {
		$_SESSION['logged_as_user'] = $login;
		header("Location: index.php");
	}
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Connexion</h1>
		<hr>
		<?php
		if (isset($error_msg))
			echo "<p>".$error_msg."</p>";
		?>
		<form class="login-form" method="post">
			<label for="login">Identifiant :</label><br>
			<input name="login" type="text" placeholder="Identifiant"><br>
			<label for="password">Mot de passe :</label><br>
			<input name="password" type="password" placeholder="Mot de passe"><br>
			<button name="submit" type="submit">Connexion</button><br>
		</form>
</div>