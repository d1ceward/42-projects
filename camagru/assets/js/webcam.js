var disable_webcam = 0;

(function() {
	var width = 640, height = 0, streaming = null;
	var video = document.getElementById('video');
	var canvas = document.getElementById('canvas');
	var photo = document.getElementById('photo');

	function clear_photo() {
		var ctx = canvas.getContext('2d');
		ctx.fillStyle = '#AAA';
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		var data = canvas.toDataURL('image/png');
		photo.setAttribute('src', data);
	}

	function take_photo() {
		var ctx = canvas.getContext('2d');
		if (width && height) {
			canvas.width = width;
			canvas.height = height;
			ctx.drawImage(video, 0, 0, width, height);
			var data = canvas.toDataURL('image/png');
			photo.setAttribute('src', data);
		} else
			clear_photo();
	}

	function startup() {
		navigator.getMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
		navigator.getMedia({video: true, audio: false},
			function (stream) {
				if (navigator.mozGetUserMedia)
					video.mozSrcObject = stream;
				else {
					var vendorURL = window.URL || window.webkitURL;
					video.src = vendorURL.createObjectURL(stream);
				}
				video.play();
			}, (error) => { console.log(error); }
		);
		
		video.addEventListener('canplay', function(ev){
			if (!streaming) {
				height = video.videoHeight / (video.videoWidth / width);
				if (isNaN(height)) {
					height = width / (4 / 3);
				}
				video.setAttribute('width', width);
				video.setAttribute('height', height);
				canvas.setAttribute('width', width);
				canvas.setAttribute('height', height);
				streaming = true;
			}
		}, false);

		document.getElementById('take-photo').addEventListener('click', function(ev){
			if (disable_webcam != 1)
				take_photo();
			ev.preventDefault();
		}, false);
		clear_photo();
	}
	window.addEventListener('load', startup, false);
})();
