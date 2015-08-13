<?
/*
function ucfirst_cyr($str) {
	return strtoupper_cyr($str[0]).substr($str,1);
}
*/

function get_IDSite() {
	return 8; // Podberi.TV
}

/* Функция строит гиперссылку по псевдоссылке в теге <ILINK>
Возмождные параметры тега:
<ILINK ID="LCD" IDBrand=10 URLBrand="Canon" IDKatalog=123 IDGood=42152 URLModel="EOS 20D">
Описание параметров в поряке приоритета.
ID - произвольный ID. Параметр используется для генерации ссылок, которые нельзя описать с
	 помошью остальных параметров, например на сайте про наушники в раздел "Наушники с микрофоном"
IDBrand - идентификатор бренда
URLBrand - если не задан идентификатор бренда, бренд можно задать через URLBrand, указав точное
	 совпадение с полями Name или URLBrand в таблице производителей.
IDKatalog - ID раздела каталога
IDGood - ID товара
URLModel - если не задан IDGood, товар можно задать через URLModel, в этом случае товар будет
	 определяться вхождением переданного значения URLModel в значиния поля URLModel товара

Если алгоритм не может привести тег ILINK к ссылке, корректной для текущего сайта, тег игнорируется.
*/
function decode_ilink($tag) {
	if (defined('IDSite'))
		$IDSite = IDSite;
	else
		$IDSite = get_IDSite();

	// Выделяем строку параметров из тега - отрезаем начало и конец
	$pos = strpos(strtoupper($tag), "ILINK");
	if ($pos !== false) {
		$tag = substr($tag, $pos+5);
	}
	$pos = strpos(strtoupper($tag), ">");
	if ($pos !== false) {
		$tag = substr($tag, 0, $pos);
	}
	$tag = trim($tag);

	$tag = str_replace(' ','&', $tag);
	$params = array();
	parse_str($tag, $params);

	// Правила для Podberi.TV
	if ($IDSite == 8) {
		// Сначала проверяем на ссылки по ID

		if (isset($params['ID'])) {
			$ID = strtoupper($params['ID']);
			if ($ID == 'LCD')
				return make_link('lcd/');
			elseif ($ID == 'PLA')
				return make_link('plazmennye/');
			elseif ($ID == 'PRO')
				return make_link('proekcionnye/');
			elseif ($ID == 'ELT')
				return make_link('elt/');
		}
		elseif (isset($params['IDKatalog'])) {
			$ID = strtoupper($params['IDKatalog']);
			if ($ID == '160')
				return make_link('lcd/');
			elseif ($ID == '159')
				return make_link('plazmennye/');
			elseif ($ID == '158')
				return make_link('proekcionnye/');
			elseif (in_array($ID,array(125)))
				return make_link('elt/');
		}
	}
	return '';
}

/*Ищет в строке теги ilink и заменяет их на корректные ссылки для текущего сайта*/
function process_ilinks($str) {
	$str2 = strtoupper($str);
	$pos = strpos($str2, '<ILINK');
	while ($pos !== false) {
		$pos2 = strpos($str, '>', $pos);
		$tag = substr($str, $pos, $pos2-$pos+1);
		$new_tag = decode_ilink($tag);
		if ($new_tag != '') {
			$new_tag = "<a href=\"$new_tag\">";
			$close_tag = '</a>';
		}
		else {
			$close_tag = '';
		}
		// Заменяем закрывающийся тег
		$pos3 = strpos($str2, '</ILINK>');
		$str = substr_replace($str, $close_tag, $pos3, 8);
		// Заменяем открывающийся тег
		$str = substr_replace($str, $new_tag, $pos, $pos2-$pos+1);

		$str2 = strtoupper($str);
		$pos = strpos($str2, '<ILINK');

	}
	return $str;
}

/*
Возвращает массив товаров выбранного раздела каталога.
$num  - количество товаров, которое требуется вернуть, если 0 - то без ограничений
$IDManufacturer - производитель, может быть не задан
$condition - условие выборки (может задаваться как строка: A1='+' или как массив строк)
$sort_select - режим сортировки при выборке (Hits / Clicks / AddDate / SalesDate)
$sort_result - режим сортировки результата  (Name / FullName /"" (если пусто, то сохраняется сортировка выборки))
*/
function get_goods_arr($IDKatalogs, $num = 0, $IDManufacturer = 0, $condition = '', $sort_select = 'AddDate', $sort_result = 'Name', $additional_fields = '') {

	$conditions = '';
	if ($IDManufacturer != 0) $conditions .= " AND M.IDManufacturer = '$IDManufacturer'";
	if ($condition != '') {
		if (is_string($condition)) $conditions .= " AND $condition";
		if (is_array($condition)) {
			foreach($condition AS $str)
				if ($str != '')
					$conditions .= " AND $str";
		}
	}
	$order_str = 'DateOfImport';
	if ($sort_select == 'AddDate') $order_str = 'DateOfImport DESC';
	elseif ($sort_select == 'SalesDate') $order_str = 'SalesStartDate DESC';
	elseif ($sort_select == 'Hits') $order_str = 'GS.Hits DESC';
	elseif ($sort_select == 'Clicks') $order_str = 'GS.Clicks DESC';
	else $order_str = $sort_select;

	$join_str = '';
	if (in_array($sort_select, array('Hits','Clicks'))) {
		$join_str = "LEFT JOIN GoodsStat GS ON (G.IDGood = GS.IDGood)";
	}

	if ($additional_fields != '') $additional_fields = ",$additional_fields";

	$query_text = "SELECT
							G.IDGood,
							G.Name,
							G.URLModel,
							M.IDManufacturer,
							M.Name Brand,
							M.URLBrand URLBrand
							$additional_fields

					FROM  	Goods G
					LEFT JOIN Manufacturers M ON (G.IDManufacturer = M.IDManufacturer)
					$join_str

					WHERE   G.IDKatalog IN ($IDKatalogs) AND
							G.DateOfImport <> '20250101000001' AND
							DateLastPrice > DATE_SUB(CURDATE(), INTERVAL ".ActualGoodsInteval." DAY)
							$conditions
					ORDER BY
							$order_str
	";

	if ($num > 0) $query_text .= " LIMIT $num";
	//echo $query_text;
	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);

	$data_arr = array();
	$sort_arr = array();
	while ($row = mysql_fetch_assoc($res)) {
		$sort_field = $row['IDGood'];
		if ($sort_result != '') {
			if ($sort_result != 'Name') $sort_field = $row['Name'];
			if ($sort_result != 'FullName') $sort_field = $row['Brand'].' '.$row['Name'];
		}
		$data_arr[$sort_field] = $row;
	}

	if ($sort_result != '') {
		ksort($data_arr);
	}

	return array_values($data_arr);

}

/* Возвращает массив брендов для раздела каталога*/
function get_brands_arr($IDKatalogs) {
	$query_text = "SELECT
							M.IDManufacturer IDManufacturer,
							M.Name Name,
							LOWER(M.URLBrand) URLBrand

					FROM  	Goods G
					LEFT JOIN Manufacturers M ON (G.IDManufacturer = M.IDManufacturer)

					WHERE   G.IDKatalog IN ($IDKatalogs) AND
							G.DateOfImport <> '20250101000001' AND
							DateLastPrice > DATE_SUB(CURDATE(), INTERVAL ".ActualGoodsInteval." DAY) AND
							M.IDManufacturer IS NOT NULL
					GROUP BY
							IDManufacturer
					ORDER BY
							Name
	";

	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);

	$data_arr = array();
	while ($row = mysql_fetch_assoc($res)) {
		$data_arr[$row['URLBrand']] = $row;
	}
	return $data_arr;
}

function get_size_field($category = '') {
	if ($category == '') $category = Category;

	if ($category == 'plazmennye') {
		$NameField = "B1";
	}
	elseif ($category == 'lcd') {
		$NameField = "B1";
	}
	elseif (($category == 'elt') or ($category == 'proekcionnye')) {
		$NameField = "B4";
	}
    elseif ($category == 'monitors') {
        $NameField = "B1";
    }
    else
        $NameField = "";


	return $NameField;
}
function get_manufacturer_arr($URLBrand) {
	$query_text = "SELECT
							*

					FROM  	Manufacturers

					WHERE   URLBrand = '".addslashes($URLBrand)."'
					LIMIT 	1
	";



	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);


	if ($row = mysql_fetch_assoc($res)) {
		return $row;
	}
	return false;

}
/* Возвращает массив размеров диагонали для раздела каталога*/
function get_sizes_arr($IDKatalogs, $category = '') {

	$NameField = get_size_field($category);

	$query_text = "SELECT
							G.{$NameField} Size

					FROM  	Goods G

					WHERE   G.IDKatalog IN ($IDKatalogs) AND
							G.DateOfImport <> '20250101000001' AND
							DateLastPrice > DATE_SUB(CURDATE(), INTERVAL ".ActualGoodsInteval." DAY) AND
							G.{$NameField} <> 0
					GROUP BY
							G.{$NameField}
					ORDER BY
							G.{$NameField}
	";



	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);

	//printAll($res);

	$data_arr = array();
	while ($row = mysql_fetch_assoc($res)) {
		$data_arr[] = $row;
	}
	return $data_arr;
}


/* Возвращает массив статей по разделу каталога
$idKatalog - раздел каталога
$level - уровень каталога, начиная с которого выводить статьи
$linear - если true - возвращается линейный список статей, если false - двухуровневый, сгруппированный по рубрикам
*/
function get_articles_arr($idKatalog, $level, $linear = false) {

	/*Сгруппируем статьи по разделам*/
	$query_text = "SELECT K.IDKatalog,K.FullName as NameKatalog,
									 R.IDRubrik, R.Name as NameRubrik, A.IDArticle, A.IDArticle, A.Name NameArticle, A.Annotation, IF(A.DateOfCreaton > DATE_SUB(CURDATE(), INTERVAL ".NewArticlesInteval." DAY),1,0) New

								FROM Katalog K,Rubrikator R,SetOfRubriks SOR,Articles A
							   WHERE (K.Sub2='$idKatalog' OR K.Sub3='$idKatalog' OR K.Sub4='$idKatalog' OR K.Sub5='$idKatalog' OR K.Sub6='$idKatalog')
								 AND K.Level >= $level
								 AND K.IDKatalog = R.IDKatalog
								 AND R.IDRubrik = SOR.IDRubrik
								 AND A.IDArticle = SOR.IDArticle
								 AND A.ExpairDate > NOW()

							GROUP BY
								R.IDRubrik,
								A.IDArticle
							ORDER BY
								K.IDKatalog,
								R.Ord,
								A.DateOfCreaton DESC
							 ";
	$resArticles = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);

	$result = array();
	while($row = mysql_fetch_assoc($resArticles)){
		if ($linear) {
			$result[] = $row;
		}
		else {
			$result[$row['IDRubrik']][] = $row;
		}

	}

	return $result;
}

function definitions() {
	// Кусочки от counter, который потом перенесем в локальное подобие counter'a
	@define("HTTP_HOST",getenv('HTTP_HOST'));
	//--получение имени домена, который записал пользователь в адрессной строке (без www)
	@define("DomainName",'www.'.str_replace('www.','',HTTP_HOST));

	$pageName=getenv('REDIRECT_URL');
	if($pageName=='') $pageName=getenv('SCRIPT_NAME');

	@define("BasePageName",basename($pageName));

	if (getenv('GEOIP_COUNTRY_CODE')){
		$country_code=getenv('GEOIP_COUNTRY_CODE');
	}
	else {$country_code='ZZ';}

	$country_code=($country_code=='UA' or $country_code=='RU')?$country_code:'Oth';
	define('CountryCode',$country_code);

	// Интервал "свежести" товара в днях, в течении которого товар будет выводится на сайте, считается от DateLastPrice
	define("ActualGoodsInteval", 15);
	define("NewArticlesInteval", 14);

	// Проверяем, не от партнера ли пришел посетитель
	define("Referer",rawurldecode(getenv('HTTP_REFERER')));
	define("UserIP",getIP());

    $geo_arr = get_geo_params(UserIP);
    if (!empty($geo_arr['IDCountryGeo'])) define('IDCountryGeo', $geo_arr['IDCountryGeo']);
    if (!empty($geo_arr['IDRegionGeo'])) define('IDRegionGeo', $geo_arr['IDRegionGeo']);
    if (!empty($geo_arr['IDCityGeo'])) define('IDCityGeo', $geo_arr['IDCityGeo']);

}

// Подготовка служебных данных
function prepare_data() {
	global $category_pages;
	global $arrCurrentKatalog;
	global $idSiteReferer;
	global $arrSessionVars;

	$arrCurrentKatalog = array('IDKatalog'=>123, 'IDBasket'=>0, 'arrSub'=>Array(0,1,123,0,0,0,0), 'Sum1'=>7000, 'Type'=>0, 'Level'=>1, 'FullName'=>'Товары', 'SingularName'=>'Товар', 'KogoMn'=>'Товаров', 'KogoEd'=>'Товара', 'OkomMn'=>'Товарах', 'OkomEd'=>'Товаре', 'LastIndexingTimeForSearch'=>'0000-00-00 00:00:00','TypeForPrice'=>0,'NameKatalogE_shop'=>'Товары','TypeForPriceE_shop'=>0,'ModePhotoDescription'=>0,'PrintPhotoDescriptionWithZeroPrice'=>'N','PrintPhotoDescriptionOnlyIfExactFit'=>'N','IsAccessories'=>'N','FillingType'=>'NoDescr','GoodResolvedNames'=>'N','PicsInModelsList'=>'N','IDsSatelliteKatalog'=>'','ListMode'=>1,'PCSchema'=>'N');

	// Разделы каталога
	$category_pages =
		array(
			'plazmennye' => array(	'IDKatalogs' => '159',
									'Name' => 'плазменные телевизоры',
									'SingleName' => 'плазменный телевизор',
									'NameKogo' => 'плазменных телевизоров',
									'NameKogoSingle' => 'плазменного телевизора',
									'Picture' => 'img/tv_plasma.gif',
									'Description' => 'Плазменные телевизоры не занимают много места. Поэтому они удачно вписываются в интерьер дома или офиса. Максимальный размер диагонали экрана давно миновал отметку в 60 дюймов, а толщина панелей становится все меньше.<BR><BR>'.
													 'Скоро уйдут в прошлое телевизоры традиционного формата. Год за годом производители готовят окончательный переход на широкоформатные экраны с соотношением сторон 16:9, как нельзя более подходящим для просмотра фильмов.<BR><BR>'.
													 'Все больше покупателей делают свой выбор в пользу плазменных телевизоров. Качественные и безопасные в эксплуатации, они умеют завоевать доверие даже закоренелого ретрограда.<BR><BR>'),
			'proekcionnye' => array('IDKatalogs' => '158',
									'Name' => 'проекционные телевизоры',
									'SingleName' => 'проекционный телевизор',
									'NameKogo' => 'проекционных телевизоров',
									'NameKogoSingle' => 'проекционного телевизора',
									'Picture' => 'img/tv3.gif',
									'Description' => 'Проекционные телевизоры занимают выгодные позиции на рынке бытовой электроники. Четкость и яркость их "картинки" отвечает самым современным требованиям времени, а такими размерами экрана не может похвастаться ни одна технология. Экранов меньше 40 дюймов у проекционных телевизоров, как правило, не бывает.<BR><BR>'.
													 'Самый популярный у домашних пользователей вариант - телевизоры с обратной проекцией. Изображение в таких моделях подается сзади на просветный экран. В таких телевизорах применяются технологии ЭЛТ, DLP, LCD, но качество во всех случаях - очень высокое. При этом, проекционные телевизоры значительно дешевле своих плоских "собратьев".<BR><BR>'),
			'lcd' => 		array(	'IDKatalogs' => '160',
									'Name' => 'LCD телевизоры',
									'SingleName' => 'LCD телевизор',
									'NameKogo' => 'LCD телевизоров',
									'NameKogoSingle' => 'LCD телевизора',
									'Picture' => 'img/tv_lcd.gif',
									'Description' => 'LCD-телевизоры - прямые наследники жидкокристаллических мониторов. Усовершенствовав ЖК-технологию, разработчики приступили к выпуску плоских и стильных многоцелевых панелей.<BR><BR>'.
													 'Главное, чем замечателен LCD, это его поистине безграничные возможности в обработке цифрового изображения. При желании владелец не только может смотреть фильмы и телепередачи, но и подключить LCD-панель вместо монитора к компьютеру.<BR><BR>'.
													 'Купить LCD-телевизор может любой желающий. В зависимости от диагонали экрана, цены разнятся от нескольких сотен до тысяч долларов.<BR><BR>'),
			'elt' => 		array(	'IDKatalogs' => '125',
									'Name' => 'ЭЛТ телевизоры',
									'SingleName' => 'ЭЛТ телевизор',
									'NameKogo' => 'ЭЛТ телевизоров',
									'NameKogoSingle' => 'ЭЛТ телевизора',
									'Picture' => 'img/tv_elt.gif',
									'Description' => 'История ЭЛТ-телевизоров насчитывает без малого сотню лет. Именно поэтому они удерживают прочные позиции на рынке. Благодаря качеству и цене современные телевизоры с кинескопом на равных конкурируют с новыми "модными" направлениями.<BR><BR>'.
													 'Технология сохраняет очень большой потенциал. Лидеры TV-индустрии продолжают выпускать телевизоры на любой вкус. Накопив богатейший арсенал технических решений, они создают модели с выпуклыми, плоскими и суперплоскими кинескопами,в самом современном дизайнерском оформлении.<BR><BR>'.
													 'Еще одно достоинство ЭЛТ-телевизоров - их долговечность. Такая вещь будет радовать покупателя и его близких десятилетиями.<BR><BR>'),
            'projector' =>  array(    'IDKatalogs' => '214',
                                    'Name' => 'Проекторы',
                                    'SingleName' => 'Проектор',
                                    'NameKogo' => 'Проекторов',
                                    'NameKogoSingle' => 'Проектора',
									'Picture' => 'img/tv_projektor.gif',
                                    'Description' => 'Главное приимущество проектора перед любым телевизором - это отношении диагонали изображения к стоимости. Даже весьма недорогая модель способна создавать изображение хорошего качества, измеряемое метрами, и ограниченного порой лишь размерами помещения.<BR><BR>'.
                                                     'Все больше и больше пользователей склоняются к тому, что для домашнего кинотеатра приобретать лучше не HD-телевизор, а именно проктор. И дело здесь не только в цене, но и в ощущениях - ведь проектор способен передать всю атмосферу настоящего кинотеатра.<BR><BR>'.
                                                     'Ну а что касается офисных презентаций, то тут у проекторов вообще нет конкурентов. Как и в сфере образования.<BR><BR>'),

			'pristavki' =>  array(    'IDKatalogs' => '33',
                                    'Name' => 'Игровые приставки',
                                    'SingleName' => 'Игровая приставка',
                                    'NameKogo' => 'Игровых приставок',
                                    'NameKogoSingle' => 'Игровой приставки',
									'Picture' => 'img/tv_play.gif',
                                    'Description' => 'Современная игровая приставка являет собой сложное устройство, ничем не уступающее персональному компьютеру. И спектр возможностей у игровых консолей не менее широк - их можно использовать не только для игр, но и для серфинга по Интернету, как медиацентр, для работы с документами... всего не перечислить.<BR><BR>'.
                                                     'Игровой процесс на консоли зачастую более интересен и удобен, нежели на персональном компьютере. Большинство игр сначала выпускаются именно для приставок, а уже потом, по прошествии порой длительного времени, и для РС.<BR><BR>'.
                                                     'Многие современные пользователи предпочитают приобрести одну игровую приставку, нежели несколько различных устройств.<BR><BR>'),
            'monitors' =>  array(    'IDKatalogs' => '157',
                                    'Name' => 'ЖК мониторы',
                                    'SingleName' => 'ЖК монитор',
                                    'NameKogo' => 'ЖК мониторов',
                                    'NameKogoSingle' => 'ЖК монитора',
									'Picture' => 'img/tv_monitor.gif',
                                    'Description' => 'LCD-мониторы одержали окончательную и безоговорочную победу над своими ЭЛТ собратьями. Развитие технологии привело к значительному снижению цен, сделав LCD-мониторы доступными для каждого пользователя.<BR><BR>'.
                                                     'Разница между LCD-мониторами и LCD-телевизорами на самом деле не так уж и велика. Особенно на фоне того, что некоторые LCD-мониторы оснащаются встроенными динамиками и ТВ-тюнерами. Кстати, при желании, в телевизор можно превратить любой монитор, докупив к нему внешний ТВ-тюнер - в таком случае для просмотра телевизионных передач не компьютер вам не потребуется.<BR><BR>'),
            'homecinema' =>  array(  'IDKatalogs' => '35',
                                    'Name' => 'Домашние кинотеатры',
                                    'SingleName' => 'Домашний кинотеатр',
                                    'NameKogo' => 'Домашних кинотеатров',
                                    'NameKogoSingle' => 'Домашнего кинотеатра',
                                    'Picture' => 'img/tv_cinema.gif',
                                    'Description' => 'По своей сути, домашний кинотеатр это набор бытовой аппаратуры, целью которого является обеспечение наиболее комфортный просмотр фильмов в домашних условиях. Главное - обеспечить объемный звук, не уступающий звуку в обычных кинотеатрах.<BR><BR>'.
                                                     'Домашние кинотеатры уже перестают быть роскошью. Удовольствие наслаждаться дома просмотром фильма на большом экране и с объемным звучанием становится все более доступным.<BR><BR>'),
            'dvd' =>  array(    'IDKatalogs' => '111',
                                    'Name' => 'DVD плееры',
                                    'SingleName' => 'DVD плеер',
                                    'NameKogo' => 'DVD плееров',
                                    'NameKogoSingle' => 'DVD плеера',
									'Picture' => 'img/tv_dvd.gif',
                                    'Description' => 'Говоря про телевизоры, нельзя не упомянуть и про такие устройства, как DVD/Blu-ray плееры. Ведь именно эти скромные и малозаметные труженики индустрии развлечений и дают нам возможность получить максимальное удовольствие от всех возможностей современного HD-телевизора.<BR><BR>'.
                                                     'Стоимость современных DVD/Blu-ray плееров колеблется в самых широких пределах - от нескольких десятков долларов до нескольких тысяч. Большинство из них способно не просто воспроизводить видеодиски, но и работать с файлами мультимедиа и оснащены функциями караоке.<BR><BR>'),

		);

    definitions();
	if(!isset($arrSessionVars['IDSiteReferer'])) checkReferer(Referer,$idSiteReferer);//--

	require_once(CommonAccessPath.'common_for_banners_show.inc');
}

function get_category_arr($category) {
	global $category_pages;
	if (isset($category_pages[$category]))
		return $category_pages[$category];
	else
		return array();
}

function get_good_pic($type, $category, $resolved_name) {

	require_once(CommonAccessPath.'common_ek_and_c-c.inc');

	$dirs = array(
		'pics' => JPG_Path,
		'pics_s' => JPG_smallPath,
		'pics_l' => JPG_zoom1Path
		);

	$path_2_pic = '';
	$arr_good = getIDGoodFromResolvedName($resolved_name, 0, false);


	if (is_array($arr_good)) {
		$path = $dirs[$type].'/'.$arr_good['IDGood'].'.jpg';
		if (file_exists($path)) {return_pic($path);exit;}

		$path = $dirs[$type].'/'.$arr_good['IDGood'].'.gif';
		if (file_exists($path)) {return_pic($path);exit;}
	}

	return_pic('img/nophoto.gif');
	exit;


}
/* Вовращает картинку логотипа бренда по строке URLBrand */
function get_logo_pic($URLBrand) {
	$brand = strtolower_cyr($URLBrand);
	if ($brand <> '') {
		$path = BrandLogoDir.'/'.$brand.'.jpg';
		if (file_exists($path)) {return_pic($path);exit;}

		$path = BrandLogoDir.'/'.$brand.'.gif';
		if (file_exists($path)) {return_pic($path);exit;}
	}

	return_pic('img/nobrand.gif');
	exit;
}

function return_pic($path) {

	if ($file = fopen($path,'r')) {

		header('HTTP/1.1 200 OK');
		header('Date: Fri, 03 Mar 2006 13:27:12 GMT');
		header('Server: Apache');
		header('Last-Modified: Fri, 03 Mar 2006 13:23:46 GMT');
		header('Accept-Ranges: bytes');
		header('Content-Length: '.filesize($path));
		header('Content-Type: image/jpeg');

		echo fread($file, filesize($path));
		fclose($file);

	}
}
// Строит ссылку, по пути к страницы (без указания сервера), подставляя правильное "начало" ссылки
function make_link($path) {
	return 'http://'.DomainName."/".$path;
}

// Строит ссылку на логотип бренда
function make_link_logo($URLBrand) {
	return 'http://'.DomainName."/pics/brands/".strtolower_cyr($URLBrand).".gif";
}

function make_link_good_picture($category, $good_arr, $type = 'pics') {

	$dirs = array(
		'pics' => JPG_Path,
		'pics_s' => JPG_smallPath,
		'pics_l' => JPG_zoom1Path
		);

	$path_2_pic = '';
	if (is_array($good_arr)) {
		$path = $dirs[$type].'/'.$good_arr['IDGood'].'.jpg';
		if (file_exists($path)) $path_2_pic = $path;

		$path = $dirs[$type].'/'.$good_arr['IDGood'].'.gif';
		if (file_exists($path)) $path_2_pic = $path;
	}

	if ($path_2_pic == '') return '';

	return 'http://'.DomainName."/$type/".Category."/{$good_arr['URLBrand']}-{$good_arr['URLModel']}.jpg";
}
/*
// Строит ссылку на все модели раздела (бренда или выборки по условию)
function make_link_section($section) {
	return 'http://'.DomainName."/models/$section/";
}
*/

// Строит ссылку на статью
function make_link_article($IDArticle) {
	return 'http://'.DomainName."/review/$IDArticle/";
}

/* Формирует ссылку на модель
$good_arr - элемент массива товаров, который возврящается функцией get_goods_arr
*/
function make_link_good($good_arr, $category = '') {

	global $category_pages;
	if ($category == '') $category = Category;
	// Ищем название бренда так, как оно задано для этого сайта
	$brand = strtolower_cyr($good_arr['URLBrand']);
	return ('http://'.DomainName."/".$category."/{$brand}/{$good_arr['URLModel']}.htm");

}

/* Формирует ссылку на бренд
$good_arr - элемент массива товаров, который возврящается функцией get_goods_arr
*/
function make_link_brand($category_ID, $brand) {
	$brand = strtolower_cyr($brand);
	return ('http://'.DomainName."/$category_ID/$brand/");
}

/* Формирует ссылку на страничку с телевизорами с выбранной диагональю

*/
function make_link_size($category_ID, $size) {
	if ($size > 0)
		return ('http://'.DomainName."/$category_ID/size-$size/");
}



/* Формирует ссылку на категорию
$category_ID - строковый ID категории (например, "lcd")
*/
function make_link_category($category_ID) {
	return ('http://'.DomainName."/$category_ID/");
}


// Выводит список брендов категории
function print_brands_menu($category, $curr_brand = '') {
	global $category_pages;
	$category_arr = get_category_arr($category);

	$brands_arr = get_brands_arr($category_arr['IDKatalogs']);

	?><!-- Бренды --><?
	?><b class="bl">Бренды <?=strtolower_cyr($category_arr['NameKogo'])?>:</b><?
	?><div class="tpd"><?

	foreach ($brands_arr AS $brand) {
		$URL = make_link_brand($category, $brand['URLBrand']);
		if ($curr_brand == strtoupper_cyr($brand['URLBrand'])) $class = ' class="ac"';else $class = '';
		?><a <?=$class?> href="<?=$URL?>"><?=$brand['Name']?></a>&nbsp; <?
	}

	?></div><?

}

// Выводит список размеров диагоналей в категории
function print_sizes_menu($category, $size = '') {
	global $category_pages;

    // Если у раздела нет поля диагонали - ничего не выводим
    if (get_size_field($category) == '') return;

	$category_arr = get_category_arr($category);

	$sizes_arr = get_sizes_arr($category_arr['IDKatalogs']);
	$columns = 3;
	$rows = ceil(count($sizes_arr) / $columns);
	for($i=0;$i<count($sizes_arr);$i++) {
		$column = floor($i / $rows);
		$row = $i-$column*$rows;
		$sizes_arr2[$column][$row] = $sizes_arr[$i];
		//echo "<BR>$column - $row - ".$sizes_arr[$i]['Size'];
	}

	?><!-- Диагонали --><?
	?><b class="bl"><?=ucfirst_cyr($category_arr['Name'])?> по диагоналям:</b><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?
	?><tr valign="top"><?
		for($i=0; $i<$columns; $i++) {
		?><td width="33%" style="padding: 10px 10px 0px 10px;"><?
			?><ul><?
				for($j=0; $j<$rows; $j++) {
					 if (isset($sizes_arr2[$i][$j])) {
						$size = $sizes_arr2[$i][$j]['Size'];
						$URL = make_link_size($category, $size);
						if (Size == strtoupper_cyr($size)) $class = ' class="ac"';else $class = '';
						?><li class="art"><a <?=$class?> href="<?=$URL?>"><?=$size?> "</a></li><?
					}
				}
			?></ul><?
		?></td><?
		}
	?></tr><?
	?></table><?

}


/*
Выводит таблицу товаров с параметрами
*/
function print_tv_table($URLBrand, $size=0, $mode = 'brand') {

	$category_arr = get_category_arr(Category);
	$size_field = get_size_field();
	$condition = '';
	if ($URLBrand != '') {
		$manifacturer_arr = get_manufacturer_arr($URLBrand);
		$IDManufacturer = $manifacturer_arr['IDManufacturer'];
	}
	if ($size != 0 and $size_field != '') {
		$condition = "$size_field = '$size'";
	}

	$category_arr = get_category_arr(Category);
	// строим массив полей, которые будут выводиться в таблице
	$fields_arr = array();
	if (Category == 'plazmennye') {
		//$fields_arr['B1'] = 'Диагональ, дюймов';
		$fields_arr['T2'] = 'Разрешение';
		//$fields_arr['E2'] = 'Разрешение (компютерное)';
		$fields_arr['E1'] = 'Формат экрана';
		$fields_arr['E3'] = 'Контрастность';
		$group_field = 'B1';
        $group_measure_str = '"';
	}
	elseif (Category == 'lcd') {
		//$fields_arr['R1'] = 'Диагональ, дюймов';
		$fields_arr['E2'] = 'Разрешение';
		$fields_arr['E1'] = 'Контрастность';
		$fields_arr["CONCAT(I2,'/',I3)"] = 'Угол обзора (верт./гор.)';
		$fields_arr['A2'] = 'Использование как монитор';
		$group_field = 'B1';
        $group_measure_str = '"';
	}
	elseif ((Category == 'elt') OR (Category == 'proekcionnye')){
		//$fields_arr['B4'] = 'Диагональ, дюймов';
		$fields_arr['E3'] = 'Развертка, Гц';
		$fields_arr['E1'] = 'Формат экрана';
		$fields_arr['T4'] = 'Мощность звука, Вт';
		$fields_arr['A2'] = 'Картинка в картинке';
		$group_field = 'B4';
        $group_measure_str = '"';
	}
    elseif (Category == 'monitors') {
        $fields_arr['E3'] = 'Тип матрицы';
        $fields_arr['E1'] = 'Разрешение';
        $fields_arr['B2'] = 'Время реакции';
        $fields_arr["CONCAT(I2,'/',I3)"] = 'Угол обзора (верт./гор.)';
        $fields_arr['A1'] = 'Динамики';
        $group_field = 'B1';
        $group_measure_str = '"';
    }
    elseif (Category == 'projector') {
        $fields_arr['I1'] = 'Слок службы лампы(ч)';
        $fields_arr['I3'] = 'Яркость';
        $fields_arr['I5'] = 'Контрастность';
        $fields_arr['E5'] = 'Реальное разрешение';
        $fields_arr['R3'] = 'Мин. проекционное растояние';
        $group_field = 'E1';
        $group_measure_str = '';
    }
    elseif (Category == 'homecinema') {
        $fields_arr['E2'] = 'Тип установки';
        $fields_arr['A29'] = 'Рекордер';
        $fields_arr['A26'] = 'Прогрессивная развёртка';
        $group_field = 'E1';
        $group_measure_str = '';
    }
    elseif (Category == 'dvd') {
        $fields_arr['A26'] = 'Прогрессивная развертка';
        $fields_arr['A33'] = 'USB порт';
        $fields_arr['A31'] = 'HDMI';
        $fields_arr['A32'] = 'Кардридер';
        $fields_arr['A29'] = 'Рекордер';
        $group_field = '';
        $group_measure_str = '';
    }

	$columns_count = count($fields_arr) + 2;

	$fields_str = "PriceMin,PriceMax,";
    if ($group_field != '') $fields_str .= "$group_field,";

	if ($mode == 'brand') $group_field = 'Brand';
	//else $fields_str .= "$group_field,";


	foreach($fields_arr AS $key=>$field) $fields_str .= $key.',';
	$fields_str = substr($fields_str, 0, -1);
	//echo $fields_str;
    if ($size_field != '') $sort_field = $size_field; else $sort_field = 'Name';
	$goods_arr_tmp = get_goods_arr($category_arr['IDKatalogs'], 0, $IDManufacturer,$condition,$sort_field,'',$fields_str);

	// Подготавливаем массив со значениями свойств
	$query_text = "SELECT
							BOP.IDProperty,
							IFC.IDItemForChoice,
							-- BOP.Name,
							IFC.Name

					FROM      Katalog K
					LEFT JOIN BasketOfPropertys BOP ON (K.IDBasket = BOP.IDBasket)
					LEFT JOIN ItemsForChoice IFC ON (BOP.IDProperty = IFC.IDProperty)
					WHERE   K.IDKatalog IN ({$category_arr['IDKatalogs']})
	";

	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);
	$prop_arr = array();
	while ($row = mysql_fetch_assoc($res)) {
		@$prop_arr[$row['IDItemForChoice']] = $row['Name'];
	}
	//echo "<PRE>";print_r($prop_arr);echo "</PRE>";

	// Формируем массив товаров с группировкой
	$goods_arr = array();
	foreach($goods_arr_tmp AS $good) {

		$group = $good[$group_field];
        if ($group_field[0] == 'E') $group = $prop_arr[$group];

		if (!isset($goods_arr[$group])) {
			$goods_arr[$group] = array('Group'=>$group,
											'Goods'=>array());
		}
		$goods_arr[$group]['Goods'][] = $good;
	}

	/*
	?><table cellpadding="0" cellspacing="0" border="0" width="100%"><?
	?><tr><?
		?><td style="padding: 10px 30px 15px 40px;"><?
	*/
			?><table cellpadding="3" cellspacing="0" border="0" width="100%"><?
				?><tr valign="top" align="center" height="22"><?
					?><td class="gr" align="left"><b>Модель</b></td><?
					foreach($fields_arr AS $name) {
						?><td class="gr"><b><?=$name?></b></td><?
					}
					?><td class="gr" align="right" width="16%"><b>Цена</b></td><?
				?></tr><?

				foreach($goods_arr AS $group_arr) {
					?><tr bgcolor="#f3f7fa"><?
						$group_name = $group_arr['Group'];
						if ($mode == 'size') $group_name = ucfirst_cyr("{$category_arr['Name']} {$manifacturer_arr['Name']} $group_name{$group_measure_str}");
						?><td colspan="<?=$columns_count?>" style="padding-left:6px; border-top: 1px solid #cdd8e6; background: url(img/bg_tit1.jpg);"  class="text"><b class="green"><?=$group_name?></b></td><?
					?></tr><?
					foreach($group_arr['Goods'] AS $good) {
						$href = make_link_good($good, Category);
						?><tr align="center"><?
							?><td align="left" nowrap><img src="img/bul_53.gif" width="17" height="11" border=0><a href="<?=$href?>"><?=$good['Name']?></b></a></td><?
							foreach($fields_arr AS $key => $name) {
								$val = $good[$key];
								if ($key[0] == 'E') $val = $prop_arr[$val];
								?><td class="gr"><?=$val?></td><?
							}
							if ($good['PriceMin'] == $good['PriceMax'])
								$price = $good['PriceMin'];

							else
								$price = $good['PriceMin'].'...'.$good['PriceMax'];

							if ($price == 0)
								$price = '';
							else
								//$price = "<a href=\"$href\">\$ $price</a>";
								$price = "$ $price";

							?><td nowrap align="right"><a href="<?=$href.'#price'?>"><?=$price?></a></td><?
						?></tr><?

					}
					?><tr><?
						?><td colspan="<?=$columns_count?>" height="5"></td><?
					?></tr><?
				}
			?></table><?
	/*
		?></td><?
	?></tr><?
	?></table><?
	*/


}

function show_top_goods($category) {
	$category_arr = get_category_arr($category);

	?><!-- Топ-3 --><?
	?><table border="0" cellspacing="0" cellpadding="0"><?
	?><tr><?
		?><td nowrap style="border-top: 1px solid #cdd8e6; border-right: 1px solid #cdd8e6; padding: 5px 15px 2px 0px;"><span class="green">Самые популярные <?=$category_arr['Name']?></span></td><?
		?><td width="100%" style="border-bottom: 1px solid #cdd8e6;">&nbsp;</td><?
	?></tr><?
	?></table><?
    $add_fields = "PriceMin, PriceMax";
    $size_field = get_size_field($category);
    if ($size_field != '') $add_fields .= ','.$size_field;

	$goods_arr = get_goods_arr($category_arr['IDKatalogs'], $num = 3, 0, '', 'Clicks', 'Name', $add_fields);

	?><div style="padding: 2px 0px 2px 0px; margin: 3px 0px 8px 0px;"><?
	foreach($goods_arr AS $good) {
		$href = make_link_good($good, $category);
			?><table border="0" cellspacing="0" cellpadding="2"><?
			?><tr valign="top"><?
				?><td><img src="img/bul_41.gif" width="11" height="10" border=0 alt=""></td><?
				?><td class="gr" style="padding-right: 10px; background: url(img/bul_7.gif); background-repeat: repeat-x;" width="100%"><span style="background: #ffffff; padding: 0px 4px 0px 0px;"><a href="<?=$href?>" class="bl"><b><?=$good['Brand'].' '.$good['Name']?></b></a><?
                if ($size_field != '') {
                    ?>&nbsp; (<?=$good[$size_field]?>")</span></td><?
                }
				?><td class="gr" align="right" nowrap>&nbsp;<a href="<?=$href.'#price'?>" class="bl">$<?=$good['PriceMin']?>...<?=$good['PriceMax']?></a></td><?
			?></tr><?
			?></table><?
	}
	?></div><?
}

// Выводит блок раздела на главной странице
function main_page_print_category_block($category) {
	global $category_pages;
	$category_arr = get_category_arr($category);

	$brands_arr = get_brands_arr($category_arr['IDKatalogs']);
	$URL_category = make_link_category($category);

	?><td style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;" width="50%"><?

	?><!-- <?=$category_arr['Name']?> --><?
	?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_start"><?
	?><tr><?

		?><td rowspan="2" style="padding: 14px 20px 0px 40px" valign="top"><img src="<?=$category_arr['Picture']?>" border=0 alt="Описания и цены на <?=$category_arr['Name']?>"></td><?
		?><td height="45" style="padding: 0px 20px 0px 0px"><h2><a href="<?=$URL_category?>" style="color:#fff"><?=ucfirst_cyr($category_arr['Name'])?></A></h2></td><?
	?></tr><?
	?><tr><?
		?><td valign="top" height="80" width="100%"><?
		?><div style="padding: 10px 20px 10px 0px;"><?
			foreach ($brands_arr AS $brand) {
				$URL = make_link_brand($category, $brand['URLBrand']);
				?><a href="<?=$URL?>"><?=$brand['Name']?></a>&nbsp; <?
			}
		?></div><?
		?></td><?
	?></tr><?
	?></table><?

	?><!-- Короткий текст с описанием группы --><?
	?><div  class="brand_logo"><?=$category_arr['Description']?><?


	show_top_goods($category);

	?><div style="width:350px;"><spacer width="1" height=1></div><?
		?><!-- Ссылка --><?
		?><table border="0" cellspacing="0" cellpadding="0" style="margin-bottom:10px;" ><?
		?><tr><?
			?><td style="padding: 0px 0px 0px 5px; border-top: 1px solid #cdd8e6; border-left: 1px solid #cdd8e6; border-bottom: 1px solid #cdd8e6;"><img src="img/ic_1.gif" width="31" height="24" border=0></td><?
			?><td style="padding: 0px 5px 4px 0px; border-top: 1px solid #cdd8e6; border-bottom: 1px solid #cdd8e6;"><a href="<?=$URL_category?>" class="green"><b>Каталог <?=$category_arr['NameKogo']?></b></a></td><?
			?><td><img src="img/corn_1.gif" width="14" height="27" border=0></td><?
		?></tr><?
		?></table><?
	?></div><?

	?></td><?
}
/* Печатает блок товаров бренда в разрезе диагоналей
$print_katalog - печатать ли название категории
*/
function print_brand_by_sizes_block($menu_mode = false) {
	global $category_pages;
	$manifacturer_arr = get_manufacturer_arr(URLBrand);
	$IDManufacturer = $manifacturer_arr['IDManufacturer'];
	$size_field = get_size_field();

    if ($size_field != '') {
        $sort_field = $size_field;
        $add_fields = $size_field;
    }
    else {
          $sort_field = 'Name';
          $add_fields = '';
    }

	$category_arr = get_category_arr(Category);
	$goods_arr_tmp = get_goods_arr($category_arr['IDKatalogs'], 0, $IDManufacturer,'',$sort_field,'',$add_fields);

	$goods_arr = array();
	foreach($goods_arr_tmp AS $good) {
        if ($size_field != '')	$size = $good[$size_field];else $size = 0;
		if (!isset($goods_arr[$size])) {
			$goods_arr[$size] = array('Size'=>$size,
											'Goods'=>array());
		}
		$goods_arr[$size]['Goods'][] = $good;
	}

	// Подсчитываем количество элентов
	$count = 0;
	foreach($goods_arr AS $size_arr) {
		if (count($size_arr['Goods']) > 0) {
			$count += 2 + count($size_arr['Goods']);
		}
	}


	?><table border="0" cellspacing="0" cellpadding="0" width="<?=$menu_mode?85:90?>%"><?
	?><tr valign="top"><?
	?><td style="padding-right:20px;"><?


    if ($size_field != '') {
    	$columns = 3;
    	$rows = ceil($count / $columns);
    	$num_rows = 0;
    	foreach($goods_arr AS $size_arr) {
    		if ($num_rows + 2 > $rows) {
    			$rows = $num_rows;
    			$num_rows = 0;
    			?></td><?
    			?><td style="padding-right:20px;"><?
    		}
    		$num_rows += 2;
    		if (!$menu_mode) {
    			?><b class="green"><?=$size_arr['Brand']?></b><?
    		}

    		if ($menu_mode) {
    			?><b class="bl"><?=$manifacturer_arr['Name']?> <?=$size_arr['Size']?>"</b><?
    			?><div class="lline_b" style="padding-left:10px;"><?
    		}
    		else {
    			/* ?><div class="header_mdl" id="txt"><h3><?=ucfirst_cyr($category_arr['Name'])?> <?=$manifacturer_arr['Name']?> <?=$size_arr['Size']?>"</h3></div><? */
    			?><div class="header_mdl" id="txt"><h3><?=$manifacturer_arr['Name']?> <?=$size_arr['Size']?>"</h3></div><?
    			?><div class="lline" id="pd_txt"><?
    		}

    		?><ul><?
    			foreach($size_arr['Goods'] AS $good) {
    				$url = make_link_good($good);
    				if (URLModel == strtoupper_cyr($good['URLModel'])) $class = ' class="ac"';else $class = '';
    				$link_text = $good['Name'];
    				if (!$menu_mode) $link_text = $manifacturer_arr['Name']. "  ".$link_text;
    				?><li class="txt"><a <?=$class?> href="<?=$url?>"><?=$link_text?></a></li><?
    				$num_rows += 1;
    			}
    		?></ul><?
    		?></div><?
    	}
    }
    else {
        foreach($goods_arr AS $size_arr) {
            $columns = 3;
            $rows = ceil(count($size_arr['Goods']) / $columns);
            $num_rows = 0;

            ?><ul><?
                foreach($size_arr['Goods'] AS $good) {
                    if ($num_rows >= $rows) {
                        $rows = $num_rows;
                        $num_rows = 0;
                        ?></ul><?
                        ?></td><?
                        ?><td style="padding-right:20px;"><?
                    }
                    $url = make_link_good($good);
                    if (URLModel == strtoupper_cyr($good['URLModel'])) $class = ' class="ac"';else $class = '';
                    $link_text = $good['Name'];
                    if (!$menu_mode) $link_text = $manifacturer_arr['Name']. "  ".$link_text;
                    ?><li class="txt"><a <?=$class?> href="<?=$url?>"><?=$link_text?></a></li><?
                    $num_rows += 1;
                }
            ?></ul><?
        }

    }
	?></td><?
	?></tr><?
	?></table><?


}


/* Печатает блок товаров в разрезе брендов */
function print_size_by_brands_block() {
	global $category_pages;
	$category_arr = get_category_arr(Category);
	$size_field = get_size_field();
	$condition = "$size_field = '".Size."'";
	$goods_arr_tmp = get_goods_arr($category_arr['IDKatalogs'], 0, 0, $condition);

	$goods_arr = array();
	foreach($goods_arr_tmp AS $good) {
		$IDManufacturer = $good['IDManufacturer'];
		if (!isset($goods_arr[$IDManufacturer])) {
			$goods_arr[$IDManufacturer] = array('IDManufacturer'=>$IDManufacturer,
											'Brand'=>$good['Brand'],
											'URLBrand'=>$good['URLBrand'],
											'Goods'=>array());



		}
		$goods_arr[$IDManufacturer]['Goods'][] = $good;
	}
	//print_r($goods_arr);
	// Подсчитываем количество элентов
	$count = 0;
	foreach($goods_arr AS $brand_arr) {
		if (count($brand_arr['Goods']) > 0) {
			$count += 2 + count($brand_arr['Goods']);
		}
	}


	?><table width="85%"  border="0" cellspacing="0" cellpadding="0"><?
	?><tr valign="top"><?

	?><td style="padding-right: 20px;" width="33%"><?

	$columns = 3;
	$rows = ceil($count / $columns);
	$num_rows = 0;
	foreach($goods_arr AS $brand_arr) {
		if ($num_rows + 1 > $rows) {
			$rows = $num_rows;
			$num_rows = 0;
			?></td><?
			?><td style="padding-right: 20px;" width="33%"><?
		}
		$num_rows += 2;

		?><b class="green"><?=$brand_arr['Brand']?></b><?
		?><div class="lline_b"><?
		?><ul><?
			foreach($brand_arr['Goods'] AS $good) {
				$url = make_link_good($good);
				?><li class="txt"><a href="<?=$url?>"><?=$good['Name']?></a></li><?
				$num_rows += 1;
			}
		?></ul><?
		?></div><?
	}
	?></td><?
	?></tr><?
	?></table><?



}


/*
Возвращает текст-описание для бренда и выбранного раздела каталога.
*/
function get_brand_text($IDKatalog = 0, $Manufacrurer = 0) {

	if (intval($Manufacrurer) === $Manufacrurer) {
		$condition = "AND BT.IDManufacturer = '$Manufacrurer'";
	}
	else {
		$condition = "AND M.URLBrand = '".strtoupper($Manufacrurer)."'";
	}

	$query_text = "SELECT
							Description
					FROM  	BrandTexts BT
					LEFT JOIN Manufacturers M ON (M.IDManufacturer = BT.IDManufacturer)

					WHERE   IDKatalog = '$IDKatalog'
							$condition

					LIMIT 1
	";

	$res = mysql_query($query_text);
	mes(mysql_error(),__FILE__,__LINE__);

	$str = '';
	if ($row = mysql_fetch_assoc($res)) {
		$str = $row['Description'];
	}
	//echo $query_text;
	return $str;
}

/*
Возвращает массив с информацией о статье
*/
function get_article_arr($IDArticle) {

	if ($IDArticle != 0) {

		$query_text = "SELECT *
						FROM Articles A
						LEFT JOIN ArticlesBlob USING (IDArticle)
						WHERE A.IDArticle = '$IDArticle'
						LIMIT 1
		";

		$res = mysql_query($query_text);
		mes(mysql_error(),__FILE__,__LINE__);
		if ($row = mysql_fetch_assoc($res)) {

			return $row;
		}
	}
	return false;
}

function print_right_menu($print_models = false) {
	global $brand;
	?><!-- Правая колонка --><?
	?><td style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?

	print_brands_menu(Category, URLBrand);

	?><div class=lline></div><?

	print_sizes_menu(Category);



	/*
	?><div class=lline></div><?
	?><!-- Поиск --><?
	?><b class="bl">Поиск модели:</b><?
	?><form method=post action="" style="margin: 5px 0px 0px 0px;"><?
		?><input type="text" name="" size="20" style="width: 80%;"/><?
		?><input type="image" src="img/but_1.gif" width="30" height="25" align="absmiddle"/><?
	?></form><?
	*/

	/* ?><img src="banner.gif" width="240" height="250" border=0 alt=""><? */
	if (defined(IDPage)) $IDPage = IDPage; else $IDPage= 801;

	// Не выводим баннер в правой колонке на странице с описанием
	//if (@$IDPage != 803) {
		$strBannerCode=showBanner(19, $IDPage);
		if ($strBannerCode!='') {
			?><div class=lline></div><?
			?><!-- Баннеры --><?
			?><div align="center" style="padding-top:5px;"><?
			echo "$strBannerCode";
			?></div><?
		}

		$strBannerCode=showBanner(24, $IDPage);
		if ($strBannerCode!='') {
			?><div class=lline></div><?
			?><!-- Баннеры --><?
			?><div align="center" style="padding-top:5px;"><?
			echo "$strBannerCode";
			?></div><?
		}
	//}

	if ($print_models) {
		?><div class=lline></div><?
		?><!-- Модели по диагоналям --><?
		/* 	?><div id="big" style="padding: 10px 30px 15px 40px;"><? */

			//print_brand_by_sizes_block(true);
		/* ?></div><? */
	}
	?><!-- Распорка --><?
	?><div style="width:265px;"><spacer width="1" height=1></div><?

	?></td><?
}

/*фнк проверяет (по переданному $referer):
 1) с какого сайта был осуществлен переход (есть ли сайт в масках MasksOfReferers) и прописываем сес. перем.:
 $arrSessionVars['IDSiteRefererType'])=$obj; $arrSessionVars['IDSiteReferer']=$idObj
 2) если переход был не с нашего сайта (а на наших сайтах мы и так знаем от куда человек и какую дом. зону ему подставлять)
  - запускаем redirect2RegionZoneOfUser()
 3) проверяет был ли осуществлен переход с сайта партнера и если да то добавляет запись об этом клике в таблицу ClicksFromPartners
*/
function checkReferer($referer,$idSiteReferer){
	//echo "checkReferer(referer=$referer,idSiteReferer=$idSiteReferer)";
	global $arrSessionVars;

	$arrSessionVars['IDSiteReferer']=0;
	$arrSessionVars['IDSiteRefererType']='none';

	/*проверять имеет смысл если длина Referer больше 4-х символов*/
	if (strlen($referer)>4 or $idSiteReferer>0){
		if ($idSiteReferer>0){
			$idObj=$idSiteReferer;
			$obj='Partners';
		}
		else{
			$arr=parse_url($referer);
			$refererDomain=strtolower(str_replace('www.','',@$arr['host']));

			$resIDSiteReferer=mysql_query("SELECT Obj,IDObj
											 From MasksOfReferers MOR
											WHERE '$refererDomain' LIKE Mask
											  AND Mask!=''
											  AND Obj='Partners'
											  AND IDObj <> 42474
										  ");
			echo mysql_error();
			//printAll($resIDSiteReferer);echo "refererDomain=$refererDomain<BR>";

			if(mysql_num_rows($resIDSiteReferer)>0){
				list($obj,$idObj)=mysql_fetch_row($resIDSiteReferer);
			}
		}

		/*Пропишем в сессию IDSiteReferer и тип реферала (ShopAndNets,Sites,Partners)*/
		if (isset($obj) and @$idObj>0) {
			$arrSessionVars['IDSiteRefererType']=$obj;
			$arrSessionVars['IDSiteReferer']=$idObj;
		}

		/*Запишем клик от партнера*/
		if (@$obj=='Partners' and @$idObj>0) {

			mysql_query("   INSERT INTO ClicksFromPartners
									SET IDHost=".IDHost.",
										DTime=Now(),
										IP=IFNULL(INET_ATON('".UserIP."'),0),
										GeoIP='".CountryCode."',
										IDSiteReferer=$idObj,
										IDSite=".IDSite.",
										URL='".DomainName.getenv('REQUEST_URI')."',
										URLReferer='".str_replace('http://','',$referer)."'
							");
			echo mysql_error();
		}

	}//--END if (strlen($referer)>4 or $idSiteReferer>0){
}

function print_arcicles_block() {
    $articles_arr_tmp = get_articles_arr(123, 2, true);

    $articles_arr = array();
    foreach ($articles_arr_tmp AS $art) {
        $articles_arr[$art['DateOfCreaton'].$art['IDArticle']] = $art;
    }

    $articles_arr_tmp = $articles_arr;

    krsort($articles_arr_tmp);
    $articles_arr = array();
    foreach ($articles_arr_tmp AS $art) {
        $articles_arr[] = $art;
        if (count($articles_arr) == 5) break;
    }

    ?><!-- Статьи --><?
    ?><div style="width: 90%;"><?
    ?><div style="border-top: 1px solid #b8c4d9; border-left: 1px solid #b8c4d9; background: url(img/bg_mdl3.gif); background-repeat: no-repeat; background-position: right bottom; padding-bottom:1px;"><?

    ?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?
    ?><tr><?
        ?><td style="background: url(img/bg_art.gif); background-repeat: no-repeat; background-position: left top; height:104px; padding: 10px 20px 10px 190px;"><?
        ?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?
        ?><tr><?
            $new = "&nbsp;<span class=\"new\">&nbsp;New&nbsp;</span>";
            ?><td width="50%" style="padding-right: 15px;"><?
                ?><ul><?
                    for($i=0;$i<3;$i++) {
                        if (isset($articles_arr[$i])) {
                            //if (getenv('REMOTE_ADDR')=='85.223.148.138') print_r($articles_arr[$i]);
                            ?><li class="art"><a href="<?=make_link_article($articles_arr[$i]['IDArticle'])?>" class="gr"><?=$articles_arr[$i]['NameArticle']?></a><?echo (($articles_arr[$i]['New'] == 1)?$new:'')?></li><?
                        }
                    }
                ?></ul><?
                ?><div style="width:315px;"><spacer width="1" height=1></div><?
            ?></td><?
            ?><td><?
                ?><ul><?
                    for($i=3;$i<5;$i++) {
                        if (isset($articles_arr[$i])) {
                            ?><li class="art"><a href="<?=make_link_article($articles_arr[$i]['IDArticle'])?>" class="gr"><?=$articles_arr[$i]['NameArticle']?></a></li><?
                        }
                    }
                    ?><li><a href="/review/" class="lbl"><b>Все статьи про телевизоры</b></a></li><?
                ?></ul><?
                ?><div style="width:315px;"><spacer width="1" height=1></div><?
            ?></td><?
        ?></tr><?
        ?></table><?

    ?></td><?
    ?></tr><?
    ?></table><?
    ?><div style="width:775px;"><spacer width="1" height=1></div><?
    ?></div><?
    ?></div><?

}

/* Определяет с помощью библиотеки геотаргетинга страну, регион и город пользователя
На момент вызова в константе UserIP должен быть записан IP пользователя */
function get_geo_params($IP) {
    global $GEOIP_REGION_NAME;
    $result_arr = array();

    if (!empty($IP)) {
        $gi = geoip_open("/usr/local/share/GeoIP/GeoIPCity.dat",GEOIP_STANDARD);

        $record = geoip_record_by_addr($gi,$IP);

        $country = $record->country_code;
        $region = $GEOIP_REGION_NAME[$record->country_code][$record->region];
        $city = $record->city;

        // Ищем страну
        if (!empty($country)) {
            $query_text = "SELECT IDRegion FROM Regions WHERE RegionType = 'Country' AND GeoRegionName = '".addslashes($country)."'";
            $res = mysql_query($query_text);
            if ($row = mysql_fetch_array($res)) {
                $result_arr['IDCountryGeo'] = $row['IDRegion'];
            }

        }

        // Ищем регион (область)
        if (!empty($region)) {
            $query_text = "SELECT IDRegion FROM Regions WHERE RegionType = 'Region' AND GeoRegionName = '".addslashes($region)."'";
            $res = mysql_query($query_text);
            if ($row = mysql_fetch_array($res)) {
                $result_arr['IDRegionGeo'] = $row['IDRegion'];
            }
        }

        // Ищем город
        if (!empty($city)) {
            $query_text = "SELECT IDRegion FROM Regions WHERE RegionType = 'City' AND GeoRegionName = '".addslashes($city)."'";
            $res = mysql_query($query_text);

            if ($row = mysql_fetch_array($res)) {
                $result_arr['IDCityGeo'] = $row['IDRegion'];
            }
        }
        //if (is_nadavi_office_ip() or IDSite == 3)   echo "$country - $region - $city<br>";


    }
    geoip_close($gi);
    //if (is_nadavi_office_ip() and IDSite == 3)  print_r($result_arr);
    return $result_arr;
}

require_once(CommonAccessPath.'/geoip/geoipcity.inc');


?>