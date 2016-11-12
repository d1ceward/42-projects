<?php
function pagination($current_page, $total_pages, $link_format) {
	$html = '<ul class="pagination">';
	if ($total_pages <= 1)
		return NULL;
	$leeway = floor(5 / 2);
	$first_page = $current_page - $leeway;
	$last_page = $current_page + $leeway;
	if ($first_page < 1) {
		$last_page += 1 - $first_page;
		$first_page = 1;
	}
	if ($last_page > $total_pages) {
		$first_page -= $last_page - $total_pages;
		$last_page = $total_pages;
	}
	if ($first_page < 1)
		$first_page = 1;
	if ($first_page != 1) {
		$html .= '<li><a href="'.$link_format.'1" title="Page 1">1</a></li>';
		$html .= '<li class="dot"><span>...</span></li>';
	}
	for ($i = $first_page; $i <= $last_page; $i++) {
		if ($i == $current_page)
			$html .= '<li class="current"><span>'.$i.'</span></li>';
		else
			$html .= '<li><a href="'.$link_format.$i.'" title="Page '.$i.'">'.$i.'</a></li>';
	}
	if ($last_page != $total_pages) {
		$html .= '<li class="dot"><span>...</span></li>';
		$html .= '<li><a href="'.$link_format.$total_pages.'" title="Page '.$total_pages.'">'.$total_pages.'</a></li>';
	}
	$html .= '</ul>';
	return $html;
}
?>
