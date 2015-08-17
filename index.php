<?

// global
function printMainPart(){

	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%" border="0" cellspacing="0" cellpadding="0"><?

		?><!-- Ïåðâàÿ ñòðîêà ñ äâóìÿ ðàçäåëàìè --><?
		?><tr valign="top"><?
			?><?=main_page_print_category_block('lcd')?><?

			?><!-- Ðàñïîðêà --><?
			?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

			?><?=main_page_print_category_block('plazmennye')?><?
		?></tr><?

		?><tr><td colspan="3" height="20"></td></tr><?

        ?><!-- âòîðàÿ ñòðîêà ñ äâóìÿ ðàçäåëàìè --><?
		?><tr valign="top"><?
			?><?=main_page_print_category_block('monitors')?><?

			?><!-- Ðàñïîðêà --><?
			?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

			?><?=main_page_print_category_block('elt')?><?
		?></tr><?

		?><tr><td colspan="3" height="20"></td></tr><?

		//if (UserIP == '82.144.200.110') {
		//if (is_nadavi_office_ip()) {

			?><!-- òðåòüÿ ñòðîêà ñ äâóìÿ ðàçäåëàìè --><?
			?><tr valign="top"><?
				?><?=main_page_print_category_block('projector')?><?

                ?><!-- Ðàñïîðêà --><?
                ?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

				?><?=main_page_print_category_block('dvd')?><?
			?></tr><?

			?><tr><td colspan="3" height="20"></td></tr><?

			?><!-- ÷åòâåðòàÿ ñòðîêà ñ äâóìÿ ðàçäåëàìè --><?
			?><tr valign="top"><?
				?><?=main_page_print_category_block('homecinema')?><?

				?><!-- Ðàñïîðêà --><?
				?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

				?><?=main_page_print_category_block('pristavki')?><?
			?></tr><?

            ?><tr><td colspan="3" height="20"></td></tr><?
        //}
	?></table><?
	?></div><?

    print_arcicles_block();


}

function getRequirements() {
	define('Title','LCD òåëåâèçîðû, ïðîåêöèîííûå è ïëàçìåííûå ïàíåëè - îïèñàíèÿ, õàðàêòåðèñòèêè, öåíû');
	define('Description','Âñå ïðî òåëåâèçîðû - ñòàòüè, îïèñàíèÿ, õàðàêòåðèñòèêè, öåíû â èíòåðíåò-ìàãàçèíàõ Ðîññèè è Óêðàèíû');
	define('Keywords','lcd òåëåâèçîðû ïðîåêöèîííûå ïëàçìåííûå ýëò îïèñàíèÿ öåíû ðîññèÿ óêðàèíà êèåâ ìîñêâà');
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
require_once(CommonAccessPath.'m1_common_lib.inc');
require_once(LibPath.'podberitv.inc');//

//----------äîïîëíèòåëüíûå ñòèëè----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- èíèöèàëèçàöèÿ íîìåðà ñòàðíèöû + ïîäêëþ÷åíèå ê áàçå
connect2DB();

getRequirements();//--ïîëó÷èì âñå íåîáõîäèìûå äàííûå

require_once(LibPath.'template.inc');

?>

