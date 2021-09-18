#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
sqlite_cmd "
create table if not exists file_id_data (
_file_id integer
);
"
#================================================
