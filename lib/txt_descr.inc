<?php


$template .= "[��� ������ ��������|���� �������� �������] {B1}\" ��������.#���������� [������|������] - {E2}\".\n";
$template .= "���������� [�������|������] {E2}\" ��������.# �������������� ������� ���������� - {E2}\" ��������.\n";
$template .= "\n";
$template .= "{A9?�� �� ��:��� ��� ���}.\n";

//mysql_connect('localhost','igor','');echo mysql_error();
//mysql_select_db('e-katalog-ua');echo mysql_error();

/*
require_once('local/definition.inc');
require(CommonAccessPath.'/common_lib.inc');

set_time_limit(30);
connect2DB();

$IDGood = '57765';
$IDKatalog = 160;
*/

function get_good_prop_value($field, $good_arr, $prop_arr) {
	$type = substr($field, 0, 1);
	if ($type == 'E') {
		// ������
		if ($good_arr[$field] == 0) $empty_field = true;
		$value = $prop_arr[$good_arr[$field]];
	}
	elseif ($type == 'B' OR $type == 'I') {
		// �����
		if ($good_arr[$field] == 0) $empty_field = true;
		$value = $good_arr[$field];
	}
	elseif ($type == 'T') {
		// �����
		if ($good_arr[$field] == '') $empty_field = true;
		$value = $good_arr[$field];
	}
	elseif ($type == 'A') {
		// ������ [A12?�����1:�����2]
		if ($good_arr[$field] == '?') $empty_field = true;

		// �������� �������� ������� - �����1 ����� �������, ���� �������� = "+", �����2 - ���� '-'
		$arr = explode('?', $field, 2);
		$field = $arr[0];
		$value = $good_arr[$field];

		if ($arr[1] == '') $value = $good_arr[$field];
		else {
			$arr = explode(':', $arr[1], 2);
			//print_r($arr);
			//echo $value;
			if ($value == '+' AND $arr[0] != '') $value = $arr[0];
			elseif ($value == '-' AND $arr[1] != '') $value = $arr[1];
			else $value = $good_arr[$field];
		}
	}
	if ($empty_field) return false;
	return $value;

}


function generate_sentence($good_arr, $prop_arr, $sentence) {

	$str_result = '';
	$current_digit = 0;

	// ������ ����������� ��������� �� �������� ����� ����������� - ���� ��������� ���������, ��� ����������� �������� #
	$sentence_arr = explode("#", $sentence);

	if (count($sentence_arr) == 0) continue;

	/* �������� ���� �� ��������� �����������.

	���� ������ ���������� �� ���������� ������� @ - �������� ��-�������, ��� ������������� ��������� �������.
	��� ������� ��� ������� �����������, � ������� ����� �������������� ����� ���������� - � ����� ������ ������ ����� �������� �����������
	� �������������� ���� ����������, ����� � ������� ����������� � � ����� ������� �����������. ������� ��������� ��� ����������� ������� � ������ ��������
	� ������� �� �� ���, ��� ����� ���������� ��� ���������.

	�� ���� ��������� ������� �� �������� ��������������� ����������� �� ������, ������ ��� ������ � �������, � ����� ��������� ������� ��� ��������� ������������,
	� ������� ����� ���� ��������� ��� ���������.
	*/
	$n = substr($IDGood, $current_digit, 2);
	//echo "-$n- ";
	$n = $n % count($sentence_arr);
	if ($current_digit++ >= strlen($IDGood)-2) $current_digit = 0;

	// � ���������� ���� ������� � ������ �������
	$sentence_arr[-1] = $sentence_arr[$n];
	ksort($sentence_arr);


	// �������� �������� ���� �������� � ��������� ������� �������� ������� - ���� �����-�� �� ������, ����������� ������� ������ �������
	foreach ($sentence_arr AS $curr_sentence) {
		// ��������� ����������� �� ��������� ����� - ������ ����� � ����������� ��������
		preg_match_all("`([^\[\]\{\}]+)|([\[\]\{\}][^\[\]\{\}]*[\[\]\{\}])`", $curr_sentence, $words);
		$words = $words[0];
		//echo '<pre>';print_r($words);echo '</pre>';

		foreach ($words AS $word) {
			if ($word[0]=='{') {
				// �������� ����
				$field = substr($word, 1, -1);
				$value = get_good_prop_value($field, $good_arr, $prop_arr);
				if ($value === false) break;
			}
		}
		if ($value !== false) break;
	}

	if ($value === false) break;
	//echo "������� �����������: $curr_sentence";

	foreach ($words AS $word) {
		if ($word[0]=='[') {
			// ������ ��������� �����
			$word = substr($word, 1, -1);
			$variants = explode('|',$word);

			// �������� ���� �� ���������
			$n = substr($IDGood, $current_digit, 2);
			//echo "-$n- ";
			$n = $n % count($variants);
			if ($current_digit++ >= strlen($IDGood)-2) $current_digit = 0;

			$word = $variants[$n];


		}
		elseif ($word[0]=='{') {
			// �������� ����
			$empty_field = false;
			$field = substr($word, 1, -1);

			$value = get_good_prop_value($field, $good_arr, $prop_arr);
			$word = $value;
		}
		//echo "<BR><$word>";
		if (!$empty_field) $str_result .= "$word";
	}

	return $str_result;

}


//preg_match("`([^\[]*)\[([^\]]*)\]`", $str, $res);
//preg_match_all("`([^\[^\]^\{^\}]*)`", $str, $res);

/* ��� ��������� ���� � �������� ����� ���� ������������ ������ �������� - ��� �������������� ������������ ��������
����� ��������� ������ ���� ��������� � ����� �������: "���������� [�������|������] {E2} ��������"
��� ����, ����� �������� �� ���������� ��� ���������� ��������, �������� ���� �� ��������� �������� �� �� �����,
� ����� ������ ��� ������������ �� ����� ��������� - � ����� ������ �� IDGood
� �������� ��������� �������� �� ����� ��������������� ������������ ����� IDGood, ��� ����, ����� ����������, ����� ��
��������� ����� ������� � ��������� ����������� [..|..].
� ���������� $current_digit ����� ������� � ���������������� ������ �����, ������� ���������� ��� ������ ������� ����������� [..|..]
�.�. ����� ������ ��� ���������� �������� �����������, �� ������� ������ �� ������ ����� IDGood, lzk ������ ������������ - �� ������� ����� � �.�.
*/

function get_podberi_good_descr($IDGood) {

	/**************************************** ���������������� ����� *********************************************************/
	$query_text = "SELECT
							G.*,
							M.Name Brand,
							M.URLBrand

					FROM      Goods G
					LEFT JOIN Manufacturers M ON (G.IDManufacturer = M.IDManufacturer)
					WHERE   IDGood = '$IDGood'
	";

	$res = mysql_query($query_text);
	echo mysql_error();

	$good_arr = mysql_fetch_assoc($res);
	$IDKatalog = $good_arr['IDKatalog'];


	$query_text = "SELECT
							BOP.IDProperty,
							IFC.IDItemForChoice,
							-- BOP.Name,
							IFC.Name

					FROM      Katalog K
					LEFT JOIN BasketOfPropertys BOP ON (K.IDBasket = BOP.IDBasket)
					LEFT JOIN ItemsForChoice IFC ON (BOP.IDProperty = IFC.IDProperty)
					WHERE   K.IDKatalog = '$IDKatalog'
	";

	$res = mysql_query($query_text);
	echo mysql_error();
	$prop_arr = array();
	while ($row = mysql_fetch_assoc($res)) {
		@$prop_arr[$row['IDItemForChoice']] = $row['Name'];
	}
	/**************************************** ���������������� ����� - ����� ************************************************/

	if (file_exists(ROOT_DIR."/templates/$IDKatalog.txt")) {
		$f = fopen(ROOT_DIR."/templates/$IDKatalog.txt",'r');
		while (!feof ($f))
			$template .= fgets($f, 100000);
	}
	else {
		return '';
	}

	$str_result = '';
	$current_digit = 0;

	// ������� ��������� �� �����������
	$sentences = explode("\n", $template);

	foreach ($sentences AS $sentence) {
		//echo "<i>$sentence</i>";
		// ������ ������ � ������� - ������ ���������� ������� ������
		if ($sentence == '') {$str_result .= '<br>';continue;}

		$str_result .= generate_sentence($good_arr, $prop_arr, $sentence).' ';

	}

	return $str_result;
}



?>