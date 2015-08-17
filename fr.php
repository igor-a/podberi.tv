<?
	?>Кирилица<?
    /* Фрейм */
	header("Content-type: text/html; charset=windows-1251");
	/* ?><script language='javascript' type='text/javascript'>document.write(navigator.appName);</script><? */
	global $p4g_type_, $p4g_id_, $p4g_partner_, $p4g_name_, $p4g_id_site_;
	$user_ip = getenv('REMOTE_ADDR');
	$url = "http://price.nadavi.com.ua/p4g_i.php?p4g_type_={$p4g_type_}&p4g_id_={$p4g_id_}&p4g_partner_={$p4g_partner_}&p4g_name_=".urlencode($p4g_name_)."&p4g_id_site_={$p4g_id_site_}&p4g_type_out_=text&user_ip_={$user_ip}";
	//echo $url;
	$f = fopen($url,"r");
	if (!$f) echo 'ups...';

	$prices_str = '';
	while ($str = fgets($f)) $prices_str .= $str;

	// Для Analitycs
	$prices_str = str_replace('<A ', "<A onClick=\"javascript:urchinTracker('/clc');\" ", $prices_str);

	echo ($prices_str);
?>
