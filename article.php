<?

function print_article($article_arr) {

	?><!-- ������� --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- ����� ����� � ��������� --><?
		?><td width="100%" style="background: url(img/bg_mdl51.gif); background-repeat: repeat-y; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2><?=Title?></h2></td><?
		?></tr><?
		?></table><?

		?><!-- ����� --><?
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

	?><!-- �������� --><?
	?><div style="width:490px;"><spacer width="1" height=1></div><?
	?></td><?

	?><!-- �������� --><?
	?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

			$articles_arr = get_articles_arr(123, 2, false);

			?><!-- ������ ������� --><?
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
	// ������������ ������
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
	?><!-- ������� --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- ����� ����� � ��������� --><?
		?><td width="100%" style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2>������ ��� ����������, ������, ������</h2></td><?
		?></tr><?
		?></table><?

		?><!-- ������ --><?
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
		?><!-- �������� --><?
		?><div style="width:490px;"><spacer width="1" height=1></div><?

		?></td><?

		?><!-- �������� --><?
		?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

		?><!-- ������ ������� --><?
		?><td style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?
		?><B>��� ������� ���������?</B></BR></BR><?

		?><table border="0" cellspacing="0" cellpadding="0" align="left" style="margin-right:10px;"><?
			?><tr><?
				?><td class="pict1"><IMG SRC="img/old_tv_1.jpg" WIDTH="90" HEIGHT="85" BORDER=0 ALT="��� ���������"></td><?
			?></tr><?
		?></table>�� ��������� ������� ��� ����� ����������� ��������� �������� ������������ ���������. ������������ ������ - �������� � �������� ������������� ����������� � �������� ������������ - �������� ������������ ���������� �� ���������� �������. � ���� �������� ������������ ���������� � ������� �������� ������������ ����� ������� ������ � ��������������� �������.<br><br><?

		?>�� ��� �����, � ����� ������������ �����������, �� ����� ���������� ������, � ��������, ������� ������� � �������� ����������. � ��� �������� ������� �� ��������� ���� ������ ������������ ��������������� �������.<?
		?><table border="0" cellpadding="0" cellspacing="0"><?
			?><tr valign="top"><?
				?><td style="padding-right: 10px;">��� ���������� ��� �� "������"? ����� ���������� ����� ������� � ��� ���� ��������� ��������� �������? ������ �������� ����� �������� ������� � �������. ������ ������ ����� ����� ��� �������� �������, ������� �������� �� ������������� �������.</td><?
				?><td align="right" class="pict1"><IMG SRC="img/old_tv_2.jpg" WIDTH="83" HEIGHT="107" BORDER=0 ALT="LCD ���������"></td><?
			?></tr><?
			?></table><br><?
		?>� ���� ������� �� �������� ������ � ������, ���� ������������� ������ ������������ �������, � ����� ���������� �������� ������� � �������, �������� � "�������������" �������� ����� �����������. �������� ������!<br><br><br><?
		?><div class=lline></div><?

		/*
		?>�� ��������� ������� ��� ����� ����������� ��������� �������� ������������ ���������. ������������ ������ - �������� � �������� ������������� ����������� � �������� ������������ - �������� ������������ ���������� �� ���������� �������. � ���� �������� ������������ ���������� � ������� �������� ������������ ����� ������� ������ � ��������������� �������.<BR><BR><?
		?>�� ��� �����, � ����� ������������ �����������, �� ����� ���������� ������, � ��������, ������� ������� � �������� ����������. � ��� �������� ������� �� ��������� ���� ������ ������������ ��������������� �������. ��� ���������� ��� �� "������"? ����� ���������� ����� ������� � ��� ���� ��������� ��������� �������? ������ �������� ����� �������� ������� � �������. ������ ������ ����� ����� ��� �������� �������, ������� �������� �� ������������� �������.<BR><BR><?
		?>� ���� ������� �� �������� ������ � ������, ���� ������������� ������ ������������ �������, � ����� ���������� �������� ������� � �������, �������� � "�������������" �������� ����� �����������. �������� ������!<BR><BR><?
		*/

		?><!-- �������� --><?
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


	define('Description','������, ������, ������ ��� ���������� - ��� ������� ���������, ������ ����������');
	define('Keywords','���������� ������ ������ ������������ ���������� lcd ������ ��� �������');
	prepare_data();

	$article_arr = get_article_arr($IDArticle);
	$title = $article_arr['Title'];
	if ($title == '') $title = '������ ��� ����������, ������, ������ ������������ - ��� ������� ���������?';
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

//----------�������������� �����----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- ������������� ������ �������� + ����������� � ����
connect2DB();

getRequirements();//--������� ��� ����������� ������

require_once(LibPath.'template.inc');

?>

