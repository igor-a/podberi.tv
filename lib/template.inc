<?

require_once(CommonAccessPath.'common_for_stat.inc');

function print_top_counter() {
?>
<?
}
function print_gemius() {
	if (defined('IDPage')) $IDPage = IDPage; else $IDPage = 801;

	$strBannerCode=showBanner(99, $IDPage);
	if ($strBannerCode!='') {
		echo "$strBannerCode";
	}
	$strBannerCode='';
}

function print_adriver() {
	// Баннер для кода отслеживания аудитории (Адривер, Володя)
	if (defined('IDPage')) $IDPage = IDPage; else $IDPage = 801;

	$strBannerCode = @showBanner(98, $IDPage);
	if ($strBannerCode != '') echo $strBannerCode;
	$strBannerCode = '';
}

function site_header() {
	?><!doctype html public "-//W3C//DTD HTML 4.0 Transitional//EN"><?
	printHeadHTML('podberitv.css');

	if (defined('IDPage')) $IDPage = IDPage; else $IDPage= 801;
	$strBannerCode=showBanner(27, $IDPage);
	if ($strBannerCode!='') {
		echo "$strBannerCode";
	}

	// Счетчики
	?><NOINDEX><?
	// Rambler
	?><!--begin of Rambler's Top100 code --><?
	?><a ref="nofollow" href="http://top100.rambler.ru/top100/"><?
	?><img src="http://counter.rambler.ru/top100.cnt?920298" alt="" width=1 height=1 border=0></a><?
	?><!--end of Top100 code--><?

?><!--Rating@Mail.ru COUNTER--><script language="JavaScript" type="text/javascript"><!--
d=document;var a='';a+=';r='+escape(d.referrer)
js=10//--></script><script language="JavaScript1.1" type="text/javascript"><!--
a+=';j='+navigator.javaEnabled()
js=11//--></script><script language="JavaScript1.2" type="text/javascript"><!--
s=screen;a+=';s='+s.width+'*'+s.height
a+=';d='+(s.colorDepth?s.colorDepth:s.pixelDepth)
js=12//--></script><script language="JavaScript1.3" type="text/javascript"><!--
js=13//--></script><script language="JavaScript" type="text/javascript"><!--
d.write('<IMG src="http://da.c7.b0.a1.top.list.ru/counter'+
'?id=1079989;js='+js+a+';rand='+Math.random()+
'" height=1 width=1/>')
if(11<js)d.write('<'+'!-- ')//--></script><noscript><img
src="http://da.c7.b0.a1.top.list.ru/counter?js=na;id=1079989"
height=1 width=1 alt=""/></noscript><script language="JavaScript" type="text/javascript"><!--
if(11<js)d.write('--'+'>')//--></script><!--/COUNTER--><?


?><!-- bigmir)net TOP 100 GIF 1x1 --><script language="javascript"><!--
bmQ='<img src=http://c.bigmir.net/?s178123&t6'
bmD=document
bmD.cookie="b=b"
if(bmD.cookie)bmQ+='&c1'
//--></script><script language="javascript1.2"><!--
bmS=screen;bmQ+='&d'+(bmS.colorDepth?bmS.colorDepth:bmS.pixelDepth)+"&r"+bmS.width;
//--></script><script language="javascript"><!--
bmF = bmD.referrer.slice(7);
((bmI=bmF.indexOf('/'))!=-1)?(bmF=bmF.substring(0,bmI)):(bmI=bmF.length);
if(bmF!=window.location.href.substring(7,7+bmI))bmQ+='&f'+escape(bmD.referrer);
bmD.write(bmQ+" border=0 width=1 height=1>");
//--></script><?

?><!--TOPPING--><script language="javascript">//<!--
mtI="122606220142";mtG="1";mtT="0";mtS='http://122606220142.c.mystat-in.net/?';
mtD=document;mtN=navigator.appName;mtR=escape(mtD.referrer);
mtW="";mtC="";mtV="0";mtJ="1";
//--></script><script language="javascript1.1">//<!--
mtV="1";mtJ = (navigator.javaEnabled()?"1":"0");
//--></script><script language="javascript1.2">//<!--
mtE=screen;mtW=mtE.width;mtN!="Netscape"?mtC=mtE.colorDepth:mtC=mtE.pixelDepth;mtV="2";
//--></script><script language="javascript1.3">//<!--
mtV="3";
//--></script><script language="javascript">//<!--
mtUrl="";mtUrl+="\""+mtS+"i"+mtI+"&t"+mtT+"&g"+mtG+"&w"+mtW+"&c"+mtC+"&r"+mtR+"&v"+mtV+"&j"+mtJ+"\"";
mtUrl="<a href=http://mytop-in.net/ target=_blank><img src="+mtUrl+"width=1 height=1 border=0 alt=\"Rated by MyTOP\"></a>";
mtD.write(mtUrl);
//--></script><noscript><a href=http://mytop-in.net/ target=_blank><img src=http://122606220142.c.mystat-in.net/?i122606220142&t0&g1&j0 width=1 height=1 border=0 alt="Rated by MyTOP"></a></noscript><?



	?></NOINDEX><?

	?><!-- главный див с фоном --><?
	?><div class="main" align="center"><?

	?><!-- H1 --><?
	if (defined('H1')) $header = H1; else $header = 'Все про телевизоры - описания, характеристики, обзоры, цены';
	?><div style="width: 90%; padding: 20px 0px 2px 0px;" align="right"><?
		?><div class="main_header"><?
			?><h1><?=$header?></h1><?
		?></div><?
	?></div><?

	?><!-- Лого + меню --><?
	?><div style="width: 90%;"><?
		?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?
		?><tr valign="bottom"><?
			?><!-- Лого --><?
			?><td><a href=""><img src="img/logo_podberitv1.gif" width="255" height="78" border=0 alt="Все про телевизоры — описания, характеристики, обзоры, цены"></a></td><?
			?><!-- Меню --><?

			?><TD class=tpd align=right width="100%"><?
			?><DIV class="top_menu"><?
				?><a href="<?=make_link_category('lcd')?>" <?=Category=='lcd'?'class="ac"':''?>>LCD</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('plazmennye')?>" <?=Category=='plazmennye'?'class="ac"':''?>>Плазменные</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('elt')?>" <?=Category=='elt'?'class="ac"':''?>>ЭЛТ</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('monitors')?>" <?=Category=='monitors'?'class="ac"':''?>>ЖК-мониторы</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('homecinema')?>" <?=Category=='homecinema'?'class="ac"':''?>>Домашние кинотеатры</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('dvd')?>" <?=Category=='dvd'?'class="ac"':''?>>DVD-плееры</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('projector')?>" <?=Category=='projector'?'class="ac"':''?>>Проекторы</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="<?=make_link_category('pristavki')?>" <?=Category=='pristavki'?'class="ac"':''?>>Игровые приставки</a>&nbsp; <b>·</b>&nbsp;&nbsp;<?
				?><a href="review" <?=defined('Articles')?'class="ac"':''?>>Статьи</a><?



			/*
			?><td width="100%" class="tpd" align="right"><?
			?><div style="border-top: 1px solid #c9d9e7; border-bottom: 1px solid #c9d9e7;"><?
			?><table border="0" cellspacing="0" cellpadding="0"><?
				?><tr><?
					?><td class="pd_menu"><a href="<?=make_link_category('lcd')?>" <?=Category=='lcd'?'class="ac"':''?>><img src="img/<?=Category=='lcd'?'bul_21.gif':'bul_2.gif'?>" width="17" height="13" border=0 align="middle" alt="Описания на LCD телевизоры">LCD</a></td><?
					?><td class="pd_menu"><a href="<?=make_link_category('plazmennye')?>" <?=Category=='plazmennye'?'class="ac"':''?>><img src="img/<?=Category=='plazmennye'?'bul_21.gif':'bul_2.gif'?>" width="17" height="13" border=0 align="middle" alt="Описания на плазменные телевизоры">Плазменные</a></td><?
					?><td class="pd_menu"><a href="<?=make_link_category('proekcionnye')?>" <?=Category=='proekcionnye'?'class="ac"':''?>><img src="img/<?=Category=='proekcionnye'?'bul_21.gif':'bul_2.gif'?>" width="17" height="13" border=0 align="middle" alt="Описания на проекционные телевизоры">Проекционные</a></td><?
					?><td class="pd_menu"><a href="<?=make_link_category('elt')?>" <?=Category=='elt'?'class="ac"':''?>><img src="img/<?=Category=='elt'?'bul_21.gif':'bul_2.gif'?>" width="17" height="13" border=0 align="middle" alt="Описания на ЭЛТ телевизоры">ЭЛТ</a></td><?
					?><td class="pd_menu"><a href="review" <?=defined('Articles')?'class="ac"':''?>><img src="img/<?=defined('Articles')?'bul_21.gif':'bul_2.gif'?>" width="17" height="13" border=0 align="middle" alt="Стати и обзоры телевизоров">Статьи</a></td><?
					?><td height=35><div style="width:15px;"><spacer width="1" height=1></div></td><?
				?></tr><?
			?></table><?
			*/

			?></div><?
			?><div style="width:600px;"><spacer width="1" height=1></div><?
			?></td><?
		?></tr><?
		?></table><?
	?></div><?

	$strBannerCode=showBanner(9, $IDPage);
	if ($strBannerCode!='') {
		?><div style="padding: 8px 0px 0px 0px;"><?
			echo "$strBannerCode";
		?></div><?
	}


}

// Выводит "подвал" страниц
function site_footer() {

	?><!-- Нижняя часть --><?

	print_gemius();

	// Пиксель-счетчик посещаемости и баннеропоказов
	echo get_pixel_img_code();
    echo get_pixel_img_code_v2();

	?><div style="background: url(img/bg_bottom.jpg); background-position: right top; background-repeat: no-repeat; border-top: 1px solid #98abbf; margin-top: 20px; height: 120px;"><?
	?><div align="left" style="width: 90%;"  class="tpd"><?
		?><!-- Копирайты и счетчики --><?
		?><table width="100%"  border="0" cellspacing="0" cellpadding="0"><?
		?><tr><?
			?><td><?
				?><table border="0" cellspacing="0" cellpadding="0" style="padding: 5px 0px 15px 0px; border-bottom: 1px solid #98abbf;"><?
				?><tr><?
					?><td><img src="img/bul_3.gif" width="39" height="32" border=0></td><?
					?><td width="100%" nowrap><span class="dbl">Podberi.TV - электронный каталог телевизоров.<BR />Описания и цены на телевизоры в интернет-магазинах России и Украины. <BR />Авторские права защищены. Подбери телевизор!<br /><?
					if (strlen($_SERVER['REQUEST_URI']) <= 1) {
						?>M.magazilla.ua - <a href='http://m.magazilla.ua/'> все цены в Вашем мобильном</a><br /><br /><?
					}
					?>&copy; <?= date('Y') ?> <a href='/about.php'>Podberi.tv</a></span></td><?
				?></tr><?
				?></table><?
			?></td><?
			?><td align="right"><?

			// Счетчики
			?><NOINDEX><?
			?><!--begin of Top100 logo--><?
			?><a ref="nofollow" href="http://top100.rambler.ru/top100/"><?
			?><img src="http://top100-images.rambler.ru/top100/banner-88x31-rambler-blue.gif" alt="Rambler's Top100" width=88 height=31 border=0></a><?
			?><!--end of Top100 logo --><?

			// mail.ru
			?>&nbsp;&nbsp;&nbsp;<?
			?><!--Rating@Mail.ru LOGO--><a ref="nofollow" target=_top href="http://top.mail.ru/jump?from=1079989"><img SRC="http://da.c7.b0.a1.top.list.ru/counter?id=1079989;t=231;l=1" border=0 height=31 width=88 alt="Рейтинг@Mail.ru"/></a><!--/LOGO--><?

			// bigmir
			?>&nbsp;&nbsp;&nbsp;<?
			?><a ref="nofollow" href="http://www.bigmir.net/" target=_blank onClick='img = new Image();img.src="http://www.bigmir.net/?cl=178123";' ><?
			?><img src=http://c.bigmir.net/?s178123&t5&l1 width=88 height=31 border=0 alt="bigmir)net TOP 100"></a><?

			// Игорь
			?><script type="text/javascript"><?
			?>var r=document.referrer;c=window.location.href;<?
			?>var re=/google\.com\.ua|google\.com|google\.ru|yandex\.ua|yandex\.ru/;<?
			?>if(r!='' && r.match(re)!=null){<?
			?>document.write("<img src='http://seo24.net.ua/_counter/?r="+<?
			?>escape(r)+"&c="+escape(c)+"&rn="+Math.random()+"'>");}<?
			?></script><?
			
			?></NOINDEX><?

			/* ?>&nbsp;&nbsp;&nbsp;<img src="img/b88_31.gif" width="88" height="31" border=0 alt=""><? */
			?><div style="width:430px;"><spacer width="1" height=1></div><?
			?></td><?
		?></tr><?
		?></table><?
	?></div><?
	?></div><?

	// Google analitics
	?>
	<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
	</script>
	<script type="text/javascript">
	_uacct = "UA-1561072-1";
	urchinTracker();
	</script>
	<?
	// End of google analitics

	print_adriver();

	?></body><?
	?></html><?
}

site_header();

printMainPart();

site_footer();
?>
