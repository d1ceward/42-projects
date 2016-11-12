var g_id = 0;

function strIsEmpty(str) {
	return (str.length === 0 || !str.trim());
}

function addNote() {
	var str = prompt("Please enter some content");
	if (!strIsEmpty(str)) {
		addNoteElement(str, g_id, 1);
		g_id++;
	}
}

function addNoteElement(str, id, post) {
	$("<div />", {id: 'note_' + id, onclick: 'removeNote(' + id + ');'}).insertAfter("#newBtn").text(str);
	if (post)
		$.post("insert.php", {id: g_id, str: str});
}

function removeNote(n) {
	if (confirm('Voulez-vous vraiment supprimer cette note ?')) {
		$('#note_' + n).remove();
		$.get("delete.php?id=" + n);
	}
}

window.onload = function () {
	$.getJSON("select.php", function (result) {
		$.each(result, function (i, field) {
			if (field) {
				addNoteElement(field, i, 0);
				g_id = parseInt(i) + 1;
			}
		});
	});
}