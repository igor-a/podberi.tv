<?

/*
���������� �������������� ���������� ����:
  http://domain/plazmennye/ - �������� �������
  http://domain/plazmennye/sony/ - �������� ������ � �������
  http://domain/plazmennye/inch-42/ - ��� ���������� ���������� ������� � �������
  http://domain/plazmennye/160/cs-100.htm - �������� ������ (160 - ������ ��������)

  ��������:
  http://domain/pics_s/koss/cs-100.jpg
  http://domain/pics/koss/cs-100.jpg
  http://domain/pics_l/koss/cs-100.jpg

  .htaccess ������ ��������� ���������:
	ErrorDocument 500 /wizard.php
	ErrorDocument 404 /wizard.php
	ErrorDocument 401 /wizard.php
	ErrorDocument 403 /wizard.php

*/

/*lib/defenition.inc - ������������ ��������������� � �������, �� �.�. ��������� Local ��� ����� ������ ��� ���������� ������
  ������� HTTP/1.0 200 Ok - ��������� ���� .inc ������*/

function counter($pageID=0,$idSiteReferer=0){
	global $arrSessionVars;

	if (@$idSiteReferer > 0) {
		definitions();
		checkReferer(@Referer, $idSiteReferer);
		// $arrSessionVars['IDSiteReferer']=$idSiteReferer;		
	}

}

header ("HTTP/1.0 200 Ok");

require('local/definition.inc'); /*���� ����������� �������� � ����������*/
require_once(CommonAccessPath.'common_lib.inc');
require_once(LibPath.'podberitv.inc');

connect2DB();

/*��������� ������ �� ���� ����� � ������ ���������*/
require(CommonAccessPath.'common_for_partner_redirect.inc');





error_reporting(E_ALL ^ E_NOTICE);
/*���������� ��������� �� URL'a ����������� ������ */
$path=getenv('REQUEST_URI');
//$path="p.tv/articles";
//$path="p.tv/pics/lcd/THOMSON-30LB020S4.jpg";
//$path="p.tv/pics/lcd/SAMSUNG-LE-20M22C.jpg";
if (strlen($path)>2){
	$arrPath=explode("/", $path);

	// ���� � URL ���� ��������� - ������� �� � ��������� ������� ������� ���� (� ���������)
	$param_pos = strpos($arrPath[count($arrPath)-1], '?');
	if ($param_pos !== false) {
		$arrPath[count($arrPath)] = substr($arrPath[count($arrPath)-1], $param_pos + 1);
		$arrPath[count($arrPath)-2] = substr($arrPath[count($arrPath)-2], 0,$param_pos);
		parse_str($arrPath[count($arrPath)-1]);//-- ����������������� ����������, ������� ������ � ���������
	}
	else {
		// ���� ���������� ��� - ��������� ������� ����� ������ ������� - ��� ��������
		$arrPath[] = '';
	}


	/* ����������� ������������ ����:
		- ���� �������� ������� � ������������� IDKatalgogs
		- ���� ������ � ������������� Size
	*/
	$level_1 = strtolower($arrPath[1]); /*���: model ��� pics*/
	$level_2 = strtolower($arrPath[2]); /*������ */
	$level_3 = urldecode($arrPath[3]); /*�����: */
	//echo "$level_1+$level_2+$level_3";
	//exit;

	$additionalStyles = "<base href=http://".getenv('HTTP_HOST')."/>";//--���� ��� ���������� ������ ��������

	/*������*/

	// ��������
	if (strtolower(substr($level_1,0,4)) == 'pics') {
		//error_reporting(0);
		$category_ = $level_2;
		$path_arr = pathinfo($level_3);
		if ($category_ == 'brands') {
			$brand = basename($path_arr['basename'], '.'.$path_arr['extension']);
			get_logo_pic($brand);
			exit;
		}
		elseif ($path_arr['extension'] == 'jpg') {
			$resolved_name_ = substr($path_arr['basename'],0,-4);
			get_good_pic($level_1, $level_2, $resolved_name_);
			exit;
		}

	}
	else {
		// ���� �� ��������, �� �������� prepare_data � ������������ ������
		global $category_pages;
		prepare_data();

		if ($level_1 == 'review') {
			global $IDArticle;
			define("Articles",1);
			$IDArticle = intval($level_2);
			include('article.php');
			exit;
		}
		else {
			// ���� ������
			foreach ($category_pages AS $key => $page) {
				if ($level_1 == $key) {
					define("IDKatalogs",$page['IDKatalogs']);
					define("Category",$level_1);

				}
			}

			// ���� ������ �� ������ - ������ ��� ����� �������� ������
			if (!defined('Category')) {
				HEADER("HTTP/1.1 404 Not Found");/*������� ������������ ���*/
				exit;
			}

			else {

				// ���� ����� ��������� ������ ��� - �������� ��������� �������
				if ($level_2 == '') {
					include('category.php');
					exit;
				}
				elseif (substr($level_2,0,5) == 'size-') {
					define("Size",substr($level_2,5));
					include('by_size.php');
					exit;
				}
				// ���� ����� ������ �������� - ������ ��� ��������� ������
				global $URLBrand;
				$URLBrand = strtoupper($level_2);
				define("URLBrand", $URLBrand);
				if ($level_3 != '') {

					list($URLModel) =  explode('.',$level_3);
					define("URLModel", $URLModel);
					include('item.php');
					exit;
				}
				else {
					// ����� - ����������� ��� ��� ��������� ������
					include('brand.php');
					exit;
				}
			}
		}
	}
}
HEADER("HTTP/1.1 404 Not Found"); /* �������� ������������ ���*/
?>




