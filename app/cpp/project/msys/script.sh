#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
sqlite_cmd "
select 'Bonjour tout lr monde';
"
#================================================
