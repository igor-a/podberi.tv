<?
/* Отдельная страница "О проекте" */
/* Второе изменение */
function print_about() {
	?>Каталог <B>Podberi.TV</B> - востребованный ресурс, предоставляющий информацию о телевизорах и сопутствующих товарах. Специалисты компании разработали удобную систему навигации по сайту - пользователи получают быстрый доступ к базе каталога, регулярно пополняющейся новыми данными о телевизорах.<BR><BR><?

	?><B>Описания<BR></B><?
	?>Описания телевизоров включают подробную информацию о характеристиках моделей, каждое описание дополнено качественными фотографиями. По возможности добавляются инструкции и пресс-релизы производителей.<BR><BR><?

	?><B>Дополнительная информация</B><BR><?
	?>База данных каталога Podberi.tv систематически обновляется. Регулярно выставляются статьи, публикуются обзоры, проводится анализ тенденций на рынке телевизоров. Также на сайте представлена информация о более 50 ведущих мировых брендах: Sony, Panasonic, Philips, Hitachi, LG, Grundig, Samsung и др.<BR><BR><?

	?><B>Покупка</B><BR><?
	?>Основы сервиса каталога - простота и функциональность. К описанию каждой модели добавлен информационный блок с ценовыми предложениями интернет-магазинов России и Украины. Данные о ценах обновляются в режиме "реального времени", предусмотрен быстрый переход на сайты магазинов-партнеров.<BR><BR><?

	?><B>Сотрудничество</B><BR><?
	?><B>Podberi.TV</B> открыт для сотрудничества с рекламодателями. "Профильный" портал - удачное вложение рекламных средств.  Пользовательская аудитория каталога постоянно расширяется за счет посетителей из России, Украины и других стран постсоветского пространства.<BR><BR><?

	$mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
	$email = "&#97;&#100;&#118;&#101;&#114;&#116;&#64;&#112;&#111;&#100;&#98;&#101;&#114;&#105;&#46;&#116;&#118;";

	?><B>Copyright</B><BR><?
	?>Материалы проекта <B>Podberi.TV</B> - описания, фотография, статьи - созданы коллективом редакторов сайта. Использование материалов без разрешения <a href="<?=$mailto.$email?>?subject=Podberi.TV">администратора</a> сайта запрещено.<BR><BR><?

	?>Контактная информация:<BR><BR><?

    ?>по вопросам рекламы: <?
	?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?

    $mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
    $email = "e-news@nadavi.net";
    ?>по вопросам использования материалов: <?
    ?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?

    $mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
    $email = "content@nadavi.net";
    ?>по вопросам контента: <?
    ?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?


}

function printMainPart(){


	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2>О проекте Podberi.TV</h2></td><?
		?></tr><?
		?></table><?

		?><!-- Ссылки --><?
		?><div class="text" style="padding: 15px 30px 15px 40px;"><?

		print_about();

		?></div><?
		?><!-- Распорка --><?
		?><div style="width:490px;"><spacer width="1" height=1></div><?

		?></td><?

		?><!-- Распорка --><?
		?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

		?><!-- Правая колонка --><?
		?><td style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?

		//print_right_menu();
		?><!-- Распорка --><?
		?><div style="width:265px;"><spacer width="1" height=1></div><?

		?></td><?
	?></tr><?
	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td></tr><?
	?></table><?
	?></div><?


}

function getRequirements() {
	define('Title','О проекте: Podberi.TV - все про телевизоры');
	define('Description','Все про телевизоры - статьи, описания, характеристики, цены в интернет-магазинах России и Украины');
	define('Keywords','lcd телевизоры проекционные плазменные элт описания цены россия украина киев москва');
	prepare_data();
}

//--DEfinition-------------------------------------
define('Category','');
define('IDPage','800');
//--END DEfinition-------------------------------------

//error_reporting(E_ALL ^ E_NOTICE);
//set_time_limit(30);

require_once('local/definition.inc');
require_once(CommonAccessPath.'common_lib.inc');
require_once(LibPath.'podberitv.inc');//

//----------дополнительные стили----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- инициализация номера старницы + подключение к базе
connect2DB();

getRequirements();//--получим все необходимые данные

require_once(LibPath.'template.inc');

?>

