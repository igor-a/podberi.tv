<?
/*
Выполняет проверку работоспособности базы данных.
1. Соединение с базой
2. Чтение из таблицы (заданный перечень)
*/


require_once('local/definition.inc');
require(CommonAccessPath.'/nadavi/common_for_nadavi.inc');

set_time_limit(20);

$fname = '../logs/spacetest.txt';
if (file_exists($fname)) unlink($fname);

$f = fopen($fname, 'w');

if (!$f) {
    echo 'Error: file open error';
    exit;
}


$str = 'Test string. Test string. Test string. Test string. Test string. Test string. Test string. ';
$str = $str.$str.$str.$str.$str.$str.$str.$str.$str;

if (!fputs($f, $str)) {
    echo 'Error: file write error';
    exit;
}

if (!fclose($f)) {
    echo 'Error: file close error';
    exit;
}

unlink($fname);

echo 'DONE';


?>
