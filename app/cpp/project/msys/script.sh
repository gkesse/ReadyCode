#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
lCheck=$(sqlite_cmd "
select count(*) as _count
from pragma_table_info('users')
where name = 'password';
")
echo $lCheck
#================================================
