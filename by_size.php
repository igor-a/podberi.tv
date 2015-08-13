<?


function printMainPart(){
	$category_arr = get_category_arr(Category);

	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2><?=ucfirst_cyr($category_arr['Name'])?></h2></td><?
		?></tr><?
		?></table><?



		?><!-- Ссылки --><?
		?><div class="text" style="padding: 15px 30px 15px 40px;"><?
		?><div class="header_mdl" id="txt"><h3><?=ucfirst_cyr($category_arr['Name'])?> с диагональю <?=Size?>"</h3></div><?
		?><div class="lline" style="padding-top: 10px; margin:0px; width:100%"><?

		//print_size_by_brands_block();

		print_tv_table('', Size, 'brand');

		?></div><?
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

	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td></tr><?

	?></table><?
	?></div><?
}

function getRequirements() {
	$category_arr = get_category_arr(Category);

	//prepare_data();
	define('Title', ucfirst_cyr($category_arr['Name']).' с диагональю '.Size.' дюймов - технические характеристики и цены');
	define('Description', 'Выбрать '.($category_arr['SingleName']).' с диагональю '.Size.' - характеристики, статьи, цены в интернет-магазинах России и Украины');
	define('Keywords','телевизоры диагональ '.Size.' lcd проекционные плазменные панели элт каталог описания статьи отзывы цены россия украина киев москва');

}

//--DEfinition-------------------------------------
//define('Category','lcd');
//define('Size','42');
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

