<?
/*«десь задаютс€ все необходимые дл€ работы Pokupaj2 константы*/
/*¬нимание!!! “олько то, что мен€етс€ в локале\на сервере*/

define('IDE_Shop','');//--номер магазина в системе E-Buy
define('IDSite',8);//--номер сайта в системе
@define('ROOT_DIR',getenv('DOCUMENT_ROOT'));//
//--
define('CommonAccessPath',ROOT_DIR.'/common_includes/');//--путь к инклудам общего доступа
define("LibPath",ROOT_DIR.'/lib/');
define("BannersDir",'./ekbn');
define("ShopLogoDir",'./logo_shop');

define('JPG_smallPath','./jpg_small/');//--путь к маленьким картинкам
define('JPG_zoom1Path','./jpg_zoom1/');//--путь к большим картинкам
define('JPG_Path','./jpg/');//--путь к обычнвм картинкам картинкам
define("BrandLogoDir",'./logo_brand'); //--Ћоготипы производителей
define("LogsDir",'./logs/');//--директори€ дл€ системных логов
define('Domain','podberi');//--"средн€€" часть доменного имени

require(CommonAccessPath.'server_definitions.inc');

if (defined("ServerName")) {
	if (ServerName == 'web') {
		/* C web запускаютс€ сервисные домены, поэтому они раюботают с мастер-базой на unit3*/
		define('DB','ek-unit3.inc');
		define('ServerCLCscript','unit3.nadavi.net');//-- сервер на которм расположен скрипт clc.php
	}
	else {
		/* ¬ остальных случа€х работаем с базой на том же хосте, где и сайт */
		define('DB','ek-'.ServerName.'.inc');
		define('ServerCLCscript',ServerName.'.nadavi.net');//-- сервер на которм расположен скрипт clc.php
	}
}
else {
	/* —тара€ ветка */
	define('IDHost',5);//--
	define('DB','ua.inc');//--

	define('ServerCLCscript','price.nadavi.com.ua');//-- сервер на которм расположен скрипт clc.php
}

require(CommonAccessPath.'common_definitions.inc');

?>