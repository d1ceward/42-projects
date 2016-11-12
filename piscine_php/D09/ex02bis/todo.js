var g_id = parseInt(getCookieValue('g_id')) || 0;

window.onload = function () {
	var notes = getCookieValue('notes').split('"');
	for (var i = 0; i < notes.length - 1; i++) {
		addNoteElement(notes[i]);
		g_id++;
		setCookieEmpty('g_id');
		setCookie('g_id', g_id);
	}
}

function strIsEmpty(str) {
	return (str.length === 0 || !str.trim());
}

function addNote() {
	var str = prompt("Please enter some content");
	if (!strIsEmpty(str)) {
		str = str.replace("\"", "''");
		str = str.replace(";", ",.");
		addNoteElement(str);
		g_id++;
		setCookie('notes', str + '"');
		setCookieEmpty('g_id');
		setCookie('g_id', g_id);
	}
}

function addNoteElement(str) {
	$("<div />", {id: 'note_' + g_id, onClick: 'removeNote(' + g_id + ');'}).insertAfter("#newBtn").text(str);
}

function removeNote(n) {
	if (confirm('Voulez-vous vraiment supprimer cette note ?')) {
		var strr = $('#note_'+n).html();
		$('#note_' + n).remove();
		var cookies = getCookieValue('notes').split('"');
		var str = "";
		for (var i = 0; i < cookies.length; i++) {
			if (cookies[i].length > 0 && cookies[i] != strr)
				str += cookies[i] + '"';
		}
		setCookieEmpty('notes');
		setCookie('notes', str);
	}
}

function setCookieEmpty(cname) {
	document.cookie = cname + "=";
}

function setCookie(cname, cvalue) {
	var old = getCookieValue(cname);
	document.cookie = cname + "=" + old + cvalue;
}

function getCookieValue(cname) {
	var name = cname + "=";
	var ca = document.cookie.split(';');
	for(var i=0; i<ca.length; i++) {
		var c = ca[i];
		while (c.charAt(0)==' ')
			c = c.substring(1);
		if (c.indexOf(name) == 0)
			return c.substring(name.length,c.length);
	}
	return "";
}