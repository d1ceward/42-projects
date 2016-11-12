#!/usr/bin/php
<?php
function ft_is_sort($array) {
	$default = $array;
	sort($array);
	foreach($array as $key => $value)
	{
		if($value!=$default[$key])
		{
			return FALSE;
		}
	}
	return TRUE;
}
?>