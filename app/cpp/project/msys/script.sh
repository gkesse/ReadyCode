#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
sqlite_cmd "
select count(*) from sqlite_master
where type = 'table'
and  name = 'login';
"

sqlite_cmd "
select name from sqlite_master;
"
#================================================
