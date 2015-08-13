<?


function printMainPart(){
	global $category_arr, $brand_arr;

	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2><?=ucfirst_cyr($category_arr['Name']).' '.$brand_arr['Name']?></h2></td><?
		?></tr><?
		?></table><?

		?><!-- Текст --><?
		?><div class="text"><?
			?><div style="padding: 15px 0px 15px 40px;"><img src="<?=make_link_logo(URLBrand)?>" border=0 alt=""></div><?
			?><div class="brand_logo"><?

				/*
				?><!-- Картинка 1 --><?
				?><table border="0" cellspacing="0" cellpadding="0" align="left" style="margin-right:10px;"><?
				?><tr><?
					?><td class="pict"><img src="img/pict_1.jpg" width="150" height="150" border=0></td><?
				?></tr><?
				?></table><?
				*/

				$text = get_brand_text(123, URLBrand);
				$text = process_ilinks($text);

				?><?=$text?><?

			?></div><?
		?></div><?

	?><!-- Модели по диагоналям --><?
	?><div id="big" style="padding: 10px 30px 15px 40px; width=100%;"><?

		// print_brand_by_sizes_block()
		print_tv_table(URLBrand, 0, 'size');

	?></div><?
	?><!-- Распорка --><?
	?><div style="width:490px;"><spacer width="1" height=1></div><?
	?></td><?

	?><!-- Распорка --><?
	?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?


		print_right_menu();

	?></tr><?
	
	// Закругленные уголки
	?><tr><?
		?><td height="55" style="background: url(img/bg_mdl52.gif); background-repeat: repeat-y; background-position: right bottom;"><div style="height:55px;"><spacer width="1" height=1></div></td><?
		?><td><div style="width:25px;"><spacer width="1" height=1></div></td><?
		?><td style="background: url(img/bg_mdl52.gif); background-repeat: repeat-y; background-position: right bottom;">&nbsp;</td><?
	?></tr><?

	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td><?
	?></tr><?

	?></table><?
	?></div><?
}

function getRequirements() {
	global $category_arr, $brand_arr;

	//prepare_data();

	$category_arr = get_category_arr(Category);
	$brand_arr = get_manufacturer_arr(URLBrand);

	define('Title', ucfirst_cyr($category_arr['Name']).' '.$brand_arr['Name'].' - каталог описаний и цены');
	define('Description', 'Каталог описаний '.($category_arr['NameKogo']).' '.$brand_arr['Name'].' - характеристики, статьи, цены в интернет-магазинах России и Украины');
	define('Keywords','lcd телевизоры проекционные плазменные панели элт каталог описания статьи отзывы цены россия украина киев москва');

}

//--DEfinition-------------------------------------
//define('Category','lcd');
define('PageID','802');
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

