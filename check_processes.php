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


$query_text = "SHOW PROCESSLIST";
$result = mysql_query($query_text);

if (mysql_num_rows($result) > 200) {
    echo 'Error: server too busy ('.mysql_num_rows($result).')';
    exit;
}

echo 'DONE';


?>
