<?

require_once('local/definition.inc');
require_once(CommonAccessPath.'common_lib.inc');
require_once(LibPath.'podberitv.inc');//

connect2DB();
prepare_data();


global $category_pages;
global $sitemap;
global $f;

$f = fopen('./_1_/sitemap.txt','w');

function add_str($str) {
	global $sitemap;
	global $f;

	//echo $str.'<BR>'."\n";
	$str = iconv('windows-1251', 'UTF-8', $str."\n");
	$sitemap .= $str;
	fputs($f, $str);
}



add_str('http://www.podberi.tv/');

foreach ($category_pages AS $category => $category_arr) {
	//$category_arr = get_category_arr($category);

	echo $category_arr['IDKatalogs'].'<BR>';

	$brands_arr = get_brands_arr($category_arr['IDKatalogs']);
	$URL_category = make_link_category($category);

	add_str($URL_category);

	foreach ($brands_arr AS $brand) {
		$URL = make_link_brand($category, $brand['URLBrand']);
		add_str($URL);
	}

	$sizes_arr = get_sizes_arr($category_arr['IDKatalogs'], $category);

	print_r($sizes_arr);
	foreach ($sizes_arr AS $size) {

		$URL = make_link_size($category, $size['Size']);
		add_str($URL);
	}


	$goods_arr = get_goods_arr($category_arr['IDKatalogs']);
	foreach ($goods_arr AS $good_arr) {
		$URL = make_link_good($good_arr, $category);
		add_str($URL);
	}

	add_str('http://www.podberi.tv/review/');

	$articles_arr = get_articles_arr(123, 2, true);
	foreach ($articles_arr AS $article) {
		$URL = make_link_article($article['IDArticle']);
		add_str($URL);
	}

	add_str('http://www.podberi.tv/about.php');

}



fclose($f);

//echo $sitemap;
?>