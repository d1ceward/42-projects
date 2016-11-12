function add_like_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location.reload();
	else {
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
		window.scrollTo(0, 0);
	}
}

function add_like(photo_id) {
	request('POST', 'pages/request/add_like.php', add_like_callback, 'photo_id=' + photo_id);
}

function delete_photo_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location.reload();
	else {
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
		window.scrollTo(0, 0);
	}
}

function delete_photo(photo_id) {
	request('POST', 'pages/request/delete_photo.php', delete_photo_callback, 'photo_id=' + photo_id);
}

function add_comment_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location.reload();
	else {
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
		window.scrollTo(0, 0);
	}
}

function add_comment(photo_id) {
	var content = document.getElementById('comment-content-' + photo_id).value;
	request('POST', 'pages/request/add_comment.php', add_comment_callback, 'content=' + content + '&photo_id=' + photo_id);
}

function delete_comment_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location.reload();
	else {
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
		window.scrollTo(0, 0);
	}
}

function delete_comment(comment_id) {
	request('POST', 'pages/request/delete_comment.php', delete_comment_callback, 'comment_id=' + comment_id);
}
