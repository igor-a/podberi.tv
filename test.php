<?
//header("Content-Type: text/html; charset=windows-1251");
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<HTML>
<HEAD>
</HEAD>
<BODY>
<script type='text/javascript'>
  window.onload=function(){
	str = 'price.nadavi.com.ua/p4g_i.php?p4g_type_=1&p4g_id_=160&p4g_partner_=0&p4g_name_=SONY+KDL-32V2000&p4g_id_site_=8&p4g_type_out_=text&user_ip_=82.144.200.110';
	//str = 'price.nadavi.com.ua/test_content.php?a=1&e=2';
	var loader=new net.ContentLoader(str, process, '', 'GET', '', 'text/html; charset=windows-1251');
	//var loader=new net.ContentLoader(str, process);
  }

  function process(){
	// alert(document.getElemenById('test').innerHTML);
	 container = document.getElementById("test");
	 container.innerHTML += this.req.responseText;
	//container = document.createElement('container');
  }

  function loadElement(){
	str = 'http://price.nadavi.com.ua/p4g_i.php?p4g_type_=1&p4g_id_=160&p4g_partner_=0&p4g_name_=Samsung+LE-26R72B&p4g_id_site_=8&p4g_type_out_=text&user_ip_=82.144.200.110';
	str = 'test.xml';
	//var loader2=new net.ContentLoader(str, process);
	var loader2=new net.ContentLoader(str, process, '', 'POST', '', 'application/xml; charset=windows-1251');
  }

</script>
<script type='text/javascript' src='ContentLoader.js'></script>
TEST
<DIV id='test'></DIV>
<DIV onClick='loadElement()'>Click me</DIV>
</BODY>
</HTML>