<?
/*
��������� �������� ����������������� ���� ������.
1. ���������� � �����
2. ������ �� ������� (�������� ��������)
*/


require_once('local/definition.inc');
require(CommonAccessPath.'/nadavi/common_for_nadavi.inc');

set_time_limit(20);

// ����������� � ��
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
