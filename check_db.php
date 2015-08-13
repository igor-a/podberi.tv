<?
/*
Выполняет проверку работоспособности базы данных.
1. Соединение с базой
2. Чтение из таблицы (заданный перечень)
*/


require_once('local/definition.inc');
require(CommonAccessPath.'/nadavi/common_for_nadavi.inc');

set_time_limit(20);

// Соединяемся с БД
if(@mysql_connect(HostName,UserName,Password)){
    if (!mysql_select_db(DBName)) {
        echo 'Error: ' . mysql_error();  ;
        exit;
    }
}
else {
    echo 'Error: ' . mysql_error();  ;
    exit;
}


// Попытка чтения из таблицы
$result = mysql_list_tables(DBName);

if (!$result) {
    echo 'Error: ' . mysql_error();
    exit;
}

$tables_arr = array();
while ($row = mysql_fetch_row($result)) {
    $tables_arr[] = $row[0];
}

// Выбираем таблицу, которую проверяем
$tables_for_check = array('PricesOfGoods', 'Accounts');

$table = '';
foreach($tables_for_check AS $curr_table) {
    if (in_array($curr_table, $tables_arr)) {
        $table = $curr_table;
        break;
    }
}

if ($table == '' and count($tables_arr) > 0) $table = $tables_arr[0];

if ($table == '') {
    echo 'Error: tables not found';
    exit;
}


$query_text = "SELECT * FROM $table LIMIT 5";
$result = mysql_query($query_text);

if (!$result) {
    echo 'MySQL Error: ' . mysql_error();
    exit;
}

echo 'DONE';


?>
