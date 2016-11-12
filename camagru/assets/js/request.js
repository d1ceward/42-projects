function add_photo_callback(response) {
	var res = JSON.parse(response);
	if (res['state'] == 1)
		window.location = 'index.php?page=photo';
	else
		document.getElementById('alert').innerHTML = '<div class="error">' + res['error'] + '</div>';
}

function add_photo() {
	var canvas = document.getElementById('canvas');
	var image_url = canvas.toDataURL('image/png');
	var description = document.getElementById('description').value;
	request('POST', 'pages/request/add_photo.php', add_photo_callback, 'image_url=' + encodeURIComponent(image_url) + '&description=' + description);
}

function logout() {
	request('POST', 'pages/request/logout.php', function() {
		window.location = ".";
	});
}

function add_mask_callback(response) {
	var res = JSON.parse(response);
	var mask_img = document.getElementById('mask-img');
	var mask_modal = document.getElementById('mask-modal');
	if (res['state'] == 1) {
		mask_img.src = "photos/masks/" + res['filename'] + ".png";
		mask_img.style.display = 'block';
		mask_modal.src = "photos/masks/" + res['filename'] + ".png";
		mask_modal.style.display = 'block';
		document.getElementById('take-photo').disabled = false;
	} else {
		document.getElementById('alert-pm').innerHTML = '<div class="error">' + res['error'] + '</div>';
		window.scrollTo(0, 0);
	}
}

function add_mask(mask_id) {
	request('POST', 'pages/request/add_mask.php', add_mask_callback, 'mask_id=' + mask_id);
}
