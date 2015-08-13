<?

function print_article($article_arr) {

	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2><?=Title?></h2></td><?
		?></tr><?
		?></table><?

		?><!-- Текст --><?
		?><div class="text"><?
			?><div style="padding: 15px 0px 15px 40px;"><h3><?=$article_arr['Name']?></h3></div><?
			?><div class="brand_logo"><?
			?><B><?=$article_arr['Annotation']?></B><BR><BR><?
			include('articles/'.$article_arr['IDArticle'].'.inc');

/*
					?><br /><br /><div style="border-top: 1px solid #c4c4c4; padding: 10px 0px 0px 0px"><?
					?><span class="bl"><b><?=$article_arr['Author']?></b></span><?
					?></div><?
*/
			?><BR><BR><?

			?></div><?
		?></div><?

	?><!-- Распорка --><?
	?><div style="width:490px;"><spacer width="1" height=1></div><?
	?></td><?

	?><!-- Распорка --><?
	?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

			$articles_arr = get_articles_arr(123, 2, false);

			?><!-- Правая колонка --><?
			?><td style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?

						foreach ($articles_arr AS $rubric) {
							$first = true;
							foreach ($rubric AS $article) {
								if ($first) {
									?><b class="bl"><?=$article['NameRubrik']?></b><?
									?><div class="lline_b" style="padding-left:10px;"><?
									?><ul><?
									$first = false;
								}

								$link = make_link_article($article['IDArticle']);
								?><li class="txt"><a href="<?=$link?>"><?=$article['NameArticle']?></a></li><?
							}
							?></ul><?
							?></div><?
						}
			?><div style="width:270px;height:1px;"><spacer width="1" height="1"/></div><?
			?></td><?

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

function all_articles() {
	?><!-- Контент --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- Левая часть с контентом --><?
		?><td width="100%" style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2>Статьи про телевизоры, советы, обзоры</h2></td><?
		?></tr><?
		?></table><?

		?><!-- Ссылки --><?
		?><div class="text" style="padding: 15px 30px 15px 40px;"><?

		$articles_arr = get_articles_arr(123, 2, false);
		$new = "&nbsp;<span class=\"new\">&nbsp;New&nbsp;</span>";

		foreach ($articles_arr AS $rubric) {
			$first = true;
			foreach ($rubric AS $article) {
				if ($first) {
					?><div class="header_mdl" id="txt"><h3><?=$article['NameRubrik']?></h3></div><?
					?><div class="lline" style="padding: 10px 0px 0px 15px; margin:0px;"><?
					?><ul><?
					$first = false;
				}

				$link = make_link_article($article['IDArticle']);

				?><li class="mdl"><a href="<?=$link?>"><b><?=$article['NameArticle']?></b></a><?echo (($article['New'] == 1)?$new:'')?><?
				?><div style="padding: 0px 0px 5px 0px" class="gr"><?=$article['Annotation']?></div><?
				?></li><?
			}
			?></ul><?
			?></div><?
		}

		?></div><?
		?><!-- Распорка --><?
		?><div style="width:490px;"><spacer width="1" height=1></div><?

		?></td><?

		?><!-- Распорка --><?
		?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

		?><!-- Правая колонка --><?
		?><td style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?
		?><B>Как выбрать телевизор?</B></BR></BR><?

		?><table border="0" cellspacing="0" cellpadding="0" align="left" style="margin-right:10px;"><?
			?><tr><?
				?><td class="pict1"><IMG SRC="img/old_tv_1.jpg" WIDTH="90" HEIGHT="85" BORDER=0 ALT="ЭЛТ телевизор"></td><?
			?></tr><?
		?></table>За последний десяток лет рынок телевизоров претерпел заметные качественные изменения. Традиционные лидеры - западные и японские производители столкнулись с сильными конкурентами - молодыми амбициозными компаниями из Азиатского региона. В этих условиях многообразие технологий и уровень развития производства стали залогом успеха и покупательского доверия.<br><br><?

		?>Не так давно, в эпоху кинескопного телевидения, на выбор покупателя влияли, в основном, размеры экранов и качество исполнения. В век цифровых решений не последнюю роль играют кардинальные технологические отличия.<?
		?><table border="0" cellpadding="0" cellspacing="0"><?
			?><tr valign="top"><?
				?><td style="padding-right: 10px;">Чем отличается ЭЛТ от "плазмы"? Какие телевизоры самые плоские и что дает поддержка цифрового сигнала? Иногда значение имеет малейшее отличие в деталях. Лишний разъем может стать той приятной мелочью, которая повлияет на окончательное решение.</td><?
				?><td align="right" class="pict1"><IMG SRC="img/old_tv_2.jpg" WIDTH="83" HEIGHT="107" BORDER=0 ALT="LCD телевизор"></td><?
			?></tr><?
			?></table><br><?
		?>В этом разделе мы помещаем статьи и обзоры, даем сравнительный анализ существующих моделей, а также раскрываем основные термины и понятия, принятые в "телевизионном" сегменте рынка электроники. Удачного выбора!<br><br><br><?
		?><div class=lline></div><?

		/*
		?>За последний десяток лет рынок телевизоров претерпел заметные качественные изменения. Традиционные лидеры - западные и японские производители столкнулись с сильными конкурентами - молодыми амбициозными компаниями из Азиатского региона. В этих условиях многообразие технологий и уровень развития производства стали залогом успеха и покупательского доверия.<BR><BR><?
		?>Не так давно, в эпоху кинескопного телевидения, на выбор покупателя влияли, в основном, размеры экранов и качество исполнения. В век цифровых решений не последнюю роль играют кардинальные технологические отличия. Чем отличается ЭЛТ от "плазмы"? Какие телевизоры самые плоские и что дает поддержка цифрового сигнала? Иногда значение имеет малейшее отличие в деталях. Лишний разъем может стать той приятной мелочью, которая повлияет на окончательное решение.<BR><BR><?
		?>В этом разделе мы помещаем статьи и обзоры, даем сравнительный анализ существующих моделей, а также раскрываем основные термины и понятия, принятые в "телевизионном" сегменте рынка электроники. Удачного выбора!<BR><BR><?
		*/

		?><!-- Распорка --><?
		?><div style="width:265px;"><spacer width="1" height=1></div><?

		?></td><?
	?></tr><?
	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td></tr><?
	?></table><?
	?></div><?
}


function printMainPart(){
	global $IDArticle, $article_arr;


	//print_r($article_arr);
	if ($article_arr != false)
		print_article($article_arr);
	else
		all_articles();
	}

function getRequirements() {
	global $IDArticle, $article_arr;


	define('Description','Обзоры, советы, статьи про телевизоры - как выбрать телевизор, обзоры технологий');
	define('Keywords','телевизоры статьи обзоры проекционные плазменные lcd панели как выбрать');
	prepare_data();

	$article_arr = get_article_arr($IDArticle);
	$title = $article_arr['Title'];
	if ($title == '') $title = 'Статьи про телевизоры, обзоры, советы специалистов - как выбрать телевизор?';
	define('Title', $title);

	//print_r($article_arr);
}

//--DEfinition-------------------------------------

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

