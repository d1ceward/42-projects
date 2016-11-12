var modal = document.getElementById('modal-photo');
var btn = document.getElementById('take-photo');
var span = document.getElementsByClassName('close')[0];
var photo = document.getElementById('photo');

btn.onclick = function() {
	modal.style.display = 'block';
}

span.onclick = function() {
	modal.style.display = 'none';
}

window.onclick = function(event) {
	if (event.target == modal) {
		modal.style.display = 'none';
	}
}

function load_file() {
	document.getElementById("uploaded_file").value = document.getElementById("file").value.replace(/^.*\\/, "");
	if (window.FileReader) {
		var reader = new FileReader();
		var file = document.getElementById('file').files[0];
		if (typeof file !== 'undefined') {
			reader.readAsDataURL(file);
			reader.onload = function(reader_event) {
				if (file.type == 'image/jpg' || file.type == 'image/jpeg' || file.type == 'image/png' || file.type == 'image/gif' || file.type == 	'image/bmp') {
					var canvas = document.getElementById('canvas');
					var video = document.getElementById('video');
					var ctx = canvas.getContext('2d');
					photo.src = reader_event.target.result;
					canvas.width = 640;
					canvas.height = 480;
					ctx.drawImage(photo, 0, 0, 640, 480);
					video.style.display = "none";
					canvas.style.display = "block";
					disable_webcam = 1;
				}
			}
		}
	}
}
