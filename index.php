<?

// Index. Local.

function printMainPart(){

	?><div style="width: 90%;" class="tpd"><?
	?><table width="100%" border="0" cellspacing="0" cellpadding="0"><?

		?><!-- ѕерва€ строка с двум€ разделами --><?
		?><tr valign="top"><?
			?><?=main_page_print_category_block('lcd')?><?

			?><!-- –аспорка --><?
			?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

			?><?=main_page_print_category_block('plazmennye')?><?
		?></tr><?

		?><tr><td colspan="3" height="20"></td></tr><?

        ?><!-- втора€ строка с двум€ разделами --><?
		?><tr valign="top"><?
			?><?=main_page_print_category_block('monitors')?><?

			?><!-- –аспорка --><?
			?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

			?><?=main_page_print_category_block('elt')?><?
		?></tr><?

		?><tr><td colspan="3" height="20"></td></tr><?

		//if (UserIP == '82.144.200.110') {
		//if (is_nadavi_office_ip()) {

			?><!-- треть€ строка с двум€ разделами --><?
			?><tr valign="top"><?
				?><?=main_page_print_category_block('projector')?><?

                ?><!-- –аспорка --><?
                ?><td><div style="width:35px;"><spacer width="1" height=1></div></td><?

				?><?=main_page_print_category_block('dvd')?><?
			?></tr><?

			?><tr><td colspan="3" height="20"></td></tr><?

			?><!-- четверта€ строка с двум€ разделами --><?
			?><tr valign="top"><?
				?><?=main_page_print_category_block('homecinema')?><?

				?><!-- –аспорка --><?
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
	define('Title','LCD телевизоры, проекционные и плазменные панели - описани€, характеристики, цены');
	define('Description','¬се про телевизоры - статьи, описани€, характеристики, цены в интернет-магазинах –оссии и ”краины');
	define('Keywords','lcd телевизоры проекционные плазменные элт описани€ цены росси€ украина киев москва');
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

//----------дополнительные стили----------------------
@$additionalStyles.="<STYLE TYPE='text/css'>\n";
$additionalStyles.="</STYLE>\n";


//-----------------------------------------------------

//counter(900);//-- инициализаци€ номера старницы + подключение к базе
connect2DB();

getRequirements();//--получим все необходимые данные

require_once(LibPath.'template.inc');

?>

