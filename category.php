<?
/* Список категории */

function printMainPart(){

	$category_arr = get_category_arr(Category);

	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2><?=ucfirst_cyr($category_arr['Name'])?></h2></td><?
		?></tr><?
		?></table><?

		?><!-- Текст --><?
		?><div class="text" style="padding: 15px 30px 15px 40px;"><?

		include('content/categories_txt/'.Category.'.inc');

		?></div><?
		?><!-- Распорка --><?
		?><div style="width:490px;"><spacer width="1" height=1></div><?

		?></td><?

		?><!-- Распорка --><?
		?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

        print_right_menu();

	?></tr><?
	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td></tr><?
	?></table><?
	?></div><?

	?><!-- Модели по брендам --><?
	?><div style="width: 90%;" class="tpd"><?

	?><table width="100%" border="0" cellspacing="0" cellpadding="0"><?
	$brands_arr = array_values(get_brands_arr($category_arr['IDKatalogs']));

	$columns = 2;
	$rows = ceil(count($brands_arr) / $columns);
	for($i=0;$i<count($brands_arr);$i++) {
		$column = floor($i / $rows);
		$row = $i-$column*$rows;
		$brands_arr2[$column][$row] = $brands_arr[$i];
	}

	for($row=0; $row < $rows; $row++) {
	?><tr valign="top"><?
		for($column=0; $column < $columns; $column++) {
			?><td width="50%" class="brand_border"><?
				if (isset($brands_arr2[$column][$row])) {
					?><!-- h3 --><?
					$url_brand = make_link_brand(Category, $brands_arr2[$column][$row]['URLBrand']);
					$h3 = ucfirst_cyr($category_arr['Name']).' '.$brands_arr2[$column][$row]['Name'];
					?><div class="header_mdl"><h3><?=$h3?></h3></div><?
					?><div class="brand_logo"><?
					?><!-- logo --><?
					?><a href="<?=$url_brand?>"><?
					?><img src="<?=make_link_logo($brands_arr2[$column][$row]['URLBrand'])?>" border=0 alt="<?=$h3.': описания и цены'?>"><?
					?></A><br /><?
					?><!-- модели --><?
						$goods_arr = get_goods_arr($category_arr['IDKatalogs'], 10, $brands_arr2[$column][$row]['IDManufacturer']);
						?><div style="padding: 5px 0px 10px 0px" class="mdl"><?
							foreach($goods_arr AS $good) {
								$url = make_link_good($good);
								?><a href="<?=$url?>"><?=$good['Name']?></a>&nbsp;&nbsp; <?
							}
							?><!-- ссылка --><?
							?><div style="padding: 5px 0px 5px 0px;"><img src="img/bul_6.gif" width="12" height="11" border=0 align="middle"><a href="<?=$url_brand?>" class="green">Каталог <?=$category_arr['NameKogo']?> <?=$brands_arr2[$column][$row]['Name']?></a></div><?
						?></div><?
					?></div><?
				}
			?></td><?

			if ($column == 0) {
				?><!-- распорка --><?
				?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?
			}
		}
	?></tr><?
	?><tr><td colspan="3" height="20"><div style="width:750px;"><spacer width="1" height=1></div></td></tr><?
	}

	?></table><?
	?></div><?
}

function getRequirements() {
	//prepare_data();
	$category_arr = get_category_arr(Category);

	define('Title', ucfirst_cyr($category_arr['Name']).' - каталог описаний и цены');
	define('Description', 'Каталог описаний '.($category_arr['NameKogo']).' - характеристики, статьи, цены в интернет-магазинах России и Украины');
	define('Keywords','lcd телевизоры проекционные плазменные панели элт каталог описания статьи отзывы цены россия украина киев москва');

}

//--DEfinition-------------------------------------

//--END DEfinition-------------------------------------

//error_reporting(E_ALL ^ E_NOTICE);
//set_time_limit(30);

require_once('local/definition.inc');
require_once(CommonAccessPath.'common_lib.inc');
require_once(CommonAccessPath.'m1_common_lib.inc');
require_once(LibPath.'podberitv.inc');//

//----------дополнительные стили----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- инициализация номера старницы + подключение к базе
//connect2DB();
getRequirements();//--получим все необходимые данные

require_once(LibPath.'template.inc');

?>

