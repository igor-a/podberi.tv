<?
/*����� �������� ��� ����������� ��� ������ Pokupaj2 ���������*/
/*��������!!! ������ ��, ��� �������� � ������\�� �������*/

define('IDE_Shop','');//--����� �������� � ������� E-Buy
define('IDSite',8);//--����� ����� � �������
@define('ROOT_DIR',getenv('DOCUMENT_ROOT'));//
//--
define('CommonAccessPath',ROOT_DIR.'/common_includes/');//--���� � �������� ������ �������
define("LibPath",ROOT_DIR.'/lib/');
define("BannersDir",'./ekbn');
define("ShopLogoDir",'./logo_shop');

define('JPG_smallPath','./jpg_small/');//--���� � ��������� ���������
define('JPG_zoom1Path','./jpg_zoom1/');//--���� � ������� ���������
define('JPG_Path','./jpg/');//--���� � ������� ��������� ���������
define("BrandLogoDir",'./logo_brand'); //--�������� ��������������
define("LogsDir",'./logs/');//--���������� ��� ��������� �����
define('Domain','podberi');//--"�������" ����� ��������� �����

require(CommonAccessPath.'server_definitions.inc');

if (defined("ServerName")) {
	if (ServerName == 'web') {
		/* C web ����������� ��������� ������, ������� ��� ��������� � ������-����� �� unit3*/
		define('DB','ek-unit3.inc');
		define('ServerCLCscript','unit3.nadavi.net');//-- ������ �� ������ ���������� ������ clc.php
	}
	else {
		/* � ��������� ������� �������� � ����� �� ��� �� �����, ��� � ���� */
		define('DB','ek-'.ServerName.'.inc');
		define('ServerCLCscript',ServerName.'.nadavi.net');//-- ������ �� ������ ���������� ������ clc.php
	}
}
else {
	/* ������ ����� */
	define('IDHost',5);//--
	define('DB','ua.inc');//--

	define('ServerCLCscript','price.nadavi.com.ua');//-- ������ �� ������ ���������� ������ clc.php
}

require(CommonAccessPath.'common_definitions.inc');

?>