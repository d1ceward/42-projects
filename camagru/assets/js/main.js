function request(method, url, callback, postData) {
	var xhttp = new XMLHttpRequest();
	xhttp.onreadystatechange = function() {
		if (xhttp.readyState == 4 && xhttp.status == 200) {
			callback(xhttp.responseText);
		}
	};
	xhttp.open(method, url, true);
	if (method == 'POST')
		xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	xhttp.send(postData);
}

function jump_to() {
	var page = document.getElementById('jump_to').value;
	window.location = 'index.php?page=gallery&page_nb=' + page;
}
