<?php


$template .= "[Эта модель оснащена|Этот телевзор оснащен] {B1}\" дисплеем.#Разрешение [экрана|панели] - {E2}\".\n";
$template .= "Разрешение [дисплея|экрана] {E2}\" пикселей.# Поддерживается высокое разрешение - {E2}\" пикселей.\n";
$template .= "\n";
$template .= "{A9?да да да:нет нет нет}.\n";

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
		// Список
		if ($good_arr[$field] == 0) $empty_field = true;
		$value = $prop_arr[$good_arr[$field]];
	}
	elseif ($type == 'B' OR $type == 'I') {
		// Число
		if ($good_arr[$field] == 0) $empty_field = true;
		$value = $good_arr[$field];
	}
	elseif ($type == 'T') {
		// Текст
		if ($good_arr[$field] == '') $empty_field = true;
		$value = $good_arr[$field];
	}
	elseif ($type == 'A') {
		// Флажок [A12?Текст1:Текст2]
		if ($good_arr[$field] == '?') $empty_field = true;

		// Выделяем аргумены функции - Текст1 будет выведен, если значение = "+", Текст2 - если '-'
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

	// Каждое предложение разбиваем на варианты этого предложения - если вариантов несколько, они разделяются символом #
	$sentence_arr = explode("#", $sentence);

	if (count($sentence_arr) == 0) continue;

	/* Выбираем один из вариантов предложения.

	Если строка начинается со служебного символа @ - выбираем по-порядку, без использования случайной выборки.
	Это сделано для сложных предложений, в которых будет использоваться много параметров - в таком случае первым будет написано предложение
	с использованием всех параметров, потом с меньшим количеством и в конце простые предложения. Система переберет все предложения начиная с самого сложного
	и выберет то из них, где может подставить все параметры.

	Во всех остальных случаях мы выбираем псевдослучайное предложение из списка, ставим его первым в очередь, и снова запускаем перебор для выявления предложкения,
	в котором могут быть заполнены все параметры.
	*/
	$n = substr($IDGood, $current_digit, 2);
	//echo "-$n- ";
	$n = $n % count($sentence_arr);
	if ($current_digit++ >= strlen($IDGood)-2) $current_digit = 0;

	// И записываем этот вариант в начало массива
	$sentence_arr[-1] = $sentence_arr[$n];
	ksort($sentence_arr);


	// Выполним проверку всех входящих в выбранный вариант значений свойств - если какое-то не задано, постараемся выбрать другой вариант
	foreach ($sentence_arr AS $curr_sentence) {
		// Разбиваем предлодежие на составные части - прямой текст и вычисляемые значения
		preg_match_all("`([^\[\]\{\}]+)|([\[\]\{\}][^\[\]\{\}]*[\[\]\{\}])`", $curr_sentence, $words);
		$words = $words[0];
		//echo '<pre>';print_r($words);echo '</pre>';

		foreach ($words AS $word) {
			if ($word[0]=='{') {
				// Значение поля
				$field = substr($word, 1, -1);
				$value = get_good_prop_value($field, $good_arr, $prop_arr);
				if ($value === false) break;
			}
		}
		if ($value !== false) break;
	}

	if ($value === false) break;
	//echo "Выбрали предложение: $curr_sentence";

	foreach ($words AS $word) {
		if ($word[0]=='[') {
			// Массив вариантов фразы
			$word = substr($word, 1, -1);
			$variants = explode('|',$word);

			// Выбираем один из вариантов
			$n = substr($IDGood, $current_digit, 2);
			//echo "-$n- ";
			$n = $n % count($variants);
			if ($current_digit++ >= strlen($IDGood)-2) $current_digit = 0;

			$word = $variants[$n];


		}
		elseif ($word[0]=='{') {
			// Значение поля
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

/* Для некоторых фраз в описании могут быть представлены разные варианты - для отоносительной уникальности описаний
такие фрагменты должны быть оформлены в таком формате: "Разрешение [дисплея|экрана] {E2} пикселей"
Для того, чтобы описание не изменялось при обновлении страницы, выбирать один из вариантов случайно мы не можем,
а будем делать это отталкиваясь от некой константы - в нашем случае от IDGood
В процессе генерации описания мы будем последовательно использовать цифры IDGood, для того, чтобы определить, какой из
вариантов фразы выбрать в очередной конструкции [..|..].
В переменной $current_digit будем хранить и инкременитровать индекс цифры, которую используем для выбора элмента конструкции [..|..]
Т.е. когда первый раз встретится подобная конструкция, мы выберем элмент по первой цифре IDGood, lzk второй контструкции - по втророй цифре и т.д.
*/

function get_podberi_good_descr($IDGood) {

	/**************************************** Подготовительная часть *********************************************************/
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
	/**************************************** Подготовительная часть - конец ************************************************/

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

	// Сначала разбираем на предложения
	$sentences = explode("\n", $template);

	foreach ($sentences AS $sentence) {
		//echo "<i>$sentence</i>";
		// Пустая строка в шаблоне - просто добаввляем перевод строки
		if ($sentence == '') {$str_result .= '<br>';continue;}

		$str_result .= generate_sentence($good_arr, $prop_arr, $sentence).' ';

	}

	return $str_result;
}



?>