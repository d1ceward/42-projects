function initFooter(){
	console.log("up");
	var c = (document.height > window.height);
	var e = document.getElementById("footer");
	e.style.position = (c) ? 'relative' : 'fixed';
	e.style.bottom = (c) ? 'auto' : "0";
	e.style.left = (c) ? 'auto': "0";
}

document.onload = initFooter;
window.onresize = initFooter;