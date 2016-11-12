<?php
if (isset($_SESSION["logged_as_user"]))
	header("Location: index.php?page=404");
else {
	$login = ft_secure(@$_POST['login']);
	$pwd = ft_secure(@$_POST['password']);
	$pwd2 = ft_secure(@$_POST['confirm_password']);
	if ($login == "")
		$error_msg = "Veuillez indiquer votre identifiant";
	else if (strlen($login) > 25)
		$error_msg = "Votre identifiant est trop long";
	else if (mysqli_num_rows(mysqli_query($db, "SELECT login FROM users WHERE login = '".$login."' LIMIT 1")) > 0)
		$error_msg = "Identifiant d&eacute;j&agrave; existant";
	else if ($pwd== "" || $pwd2 == "")
		$error_msg = "Vous n'avez pas rempli les deux mots de passe";
	else if (strlen($pwd) > 100)
		$error_msg = "Votre mot de passe est trop long";
	else if ($pwd != $pwd2)
		$error_msg = "Les deux mots de passe ne sont pas identiques";
	else {
		mysqli_query($db, "INSERT INTO users VALUES (NULL, '".$login."', '".crypt_pwd($pwd)."', 0)");
		header("Location: index.php?page=login");
	}
}
require_once('includes/header.php');
?>
<div class="section">
	<div class="wrap group">
		<h1>Cr&eacute;er un compte</h1>
		<hr>
		<?php
		if (isset($error_msg))
			echo "<p>".$error_msg."</p>";
		?>
		<form class="login-form" method="post">
			<label for="login">Identifiant :</label><br>
			<input name="login" id="register_login" type="text" placeholder="Identifiant"><br>
			<label for="password">Mot de passe :</label><br>
			<input name="password" id="register_pwd" type="password" placeholder="Mot de passe"><br>
			<label for="confirm_password">Confirmation du mot de passe :</label><br>
			<input name="confirm_password" id="register_pwd" type="password" placeholder="Confirmation du mot de passe"><br>
			<button name="submit" type="submit">Cr&eacute;er le compte</button><br>
		</form>
	</div>
</div>