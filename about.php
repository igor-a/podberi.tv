<?
/* ��������� �������� "� �������" */
function print_about() {
	?>������� <B>Podberi.TV</B> - �������������� ������, ��������������� ���������� � ����������� � ������������� �������. ����������� �������� ����������� ������� ������� ��������� �� ����� - ������������ �������� ������� ������ � ���� ��������, ��������� ������������� ������ ������� � �����������.<BR><BR><?

	?><B>��������<BR></B><?
	?>�������� ����������� �������� ��������� ���������� � ��������������� �������, ������ �������� ��������� ������������� ������������. �� ����������� ����������� ���������� � �����-������ ��������������.<BR><BR><?

	?><B>�������������� ����������</B><BR><?
	?>���� ������ �������� Podberi.tv �������������� �����������. ��������� ������������ ������, ����������� ������, ���������� ������ ��������� �� ����� �����������. ����� �� ����� ������������ ���������� � ����� 50 ������� ������� �������: Sony, Panasonic, Philips, Hitachi, LG, Grundig, Samsung � ��.<BR><BR><?

	?><B>�������</B><BR><?
	?>������ ������� �������� - �������� � ����������������. � �������� ������ ������ �������� �������������� ���� � �������� ������������� ��������-��������� ������ � �������. ������ � ����� ����������� � ������ "��������� �������", ������������ ������� ������� �� ����� ���������-���������.<BR><BR><?

	?><B>��������������</B><BR><?
	?><B>Podberi.TV</B> ������ ��� �������������� � ���������������. "����������" ������ - ������� �������� ��������� �������.  ���������������� ��������� �������� ��������� ����������� �� ���� ����������� �� ������, ������� � ������ ����� �������������� ������������.<BR><BR><?

	$mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
	$email = "&#97;&#100;&#118;&#101;&#114;&#116;&#64;&#112;&#111;&#100;&#98;&#101;&#114;&#105;&#46;&#116;&#118;";

	?><B>Copyright</B><BR><?
	?>��������� ������� <B>Podberi.TV</B> - ��������, ����������, ������ - ������� ����������� ���������� �����. ������������� ���������� ��� ���������� <a href="<?=$mailto.$email?>?subject=Podberi.TV">��������������</a> ����� ���������.<BR><BR><?

	?>���������� ����������:<BR><BR><?

    ?>�� �������� �������: <?
	?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?

    $mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
    $email = "e-news@nadavi.net";
    ?>�� �������� ������������� ����������: <?
    ?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?

    $mailto = "&#109;&#97;&#105;&#108;&#116;&#111;&#58;";
    $email = "content@nadavi.net";
    ?>�� �������� ��������: <?
    ?><a href="<?=$mailto.$email?>?subject=Podberi.TV"><?=$email?></a><BR><?


}

function printMainPart(){


	?><!-- ������� --><?
	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?

	?><tr valign="top"><?

		?><!-- ����� ����� � ��������� --><?
		?><td width="100%" style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom;"><?
		?><!-- H2 --><?
		?><table width="100%" border="0" cellspacing="0" cellpadding="0" class="block_sec"><?
		?><tr><?
			?><td height="30" style="padding: 0px 20px 0px 40px"><h2>� ������� Podberi.TV</h2></td><?
		?></tr><?
		?></table><?

		?><!-- ������ --><?
		?><div class="text" style="padding: 15px 30px 15px 40px;"><?

		print_about();

		?></div><?
		?><!-- �������� --><?
		?><div style="width:490px;"><spacer width="1" height=1></div><?

		?></td><?

		?><!-- �������� --><?
		?><td style="border-top: 1px solid #c9d9e7;"><div style="width:25px;"><spacer width="1" height=1></div></td><?

		?><!-- ������ ������� --><?
		?><td style="background: url(img/bg_mdl2.gif); background-repeat: no-repeat; background-position: right bottom; border-top: 1px solid #c9d9e7; padding: 8px 20px 30px 0px;"><?

		//print_right_menu();
		?><!-- �������� --><?
		?><div style="width:265px;"><spacer width="1" height=1></div><?

		?></td><?
	?></tr><?
	?><tr><td colspan="3" height="10"><div style="width:545px;"><spacer width="1" height=1></div></td></tr><?
	?></table><?
	?></div><?


}

function getRequirements() {
	define('Title','� �������: Podberi.TV - ��� ��� ����������');
	define('Description','��� ��� ���������� - ������, ��������, ��������������, ���� � ��������-��������� ������ � �������');
	define('Keywords','lcd ���������� ������������ ���������� ��� �������� ���� ������ ������� ���� ������');
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

//----------�������������� �����----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- ������������� ������ �������� + ����������� � ����
connect2DB();

getRequirements();//--������� ��� ����������� ������

require_once(LibPath.'template.inc');

?>

