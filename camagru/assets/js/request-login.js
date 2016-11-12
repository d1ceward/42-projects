function register_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location = 'index.php?page=login&alert=disable';
	else
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
}

function register() {
	var login = document.getElementById('login_field').value;
	var pwd = document.getElementById('pwd_field').value;
	var confirm_pwd = document.getElementById('confirm_field').value;
	var email = document.getElementById('email_field').value;
	request('POST', 'pages/request/register.php', register_callback, 'login=' + login + '&pwd=' + pwd + '&confirm_pwd=' + confirm_pwd + '&email=' + email);
}

function login_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location = '.';
	else
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
}

function login() {
	var login = document.getElementById('login_field').value;
	var pwd = document.getElementById('pwd_field').value;
	request('POST', 'pages/request/login.php', login_callback, 'login=' + login + '&pwd=' + pwd);
}

function recovery_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location = 'index.php?page=login&alert=recovery';
	else
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
}

function recovery() {
	var email = document.getElementById('email_field').value;
	request('POST', 'pages/request/recovery.php', recovery_callback, 'email=' + email);
}

function reset_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location = 'index.php?page=login&alert=success_pwd';
	else
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
}

function reset() {
	var pwd = document.getElementById('pwd_field').value;
	var confirm_pwd = document.getElementById('confirm_field').value;
	var login = document.getElementById('login_field').value;
	var token = document.getElementById('token_field').value;
	request('POST', 'pages/request/reset.php', reset_callback, 'login=' + login + '&pwd=' + pwd + '&confirm_pwd=' + confirm_pwd + '&token=' + token);
}
