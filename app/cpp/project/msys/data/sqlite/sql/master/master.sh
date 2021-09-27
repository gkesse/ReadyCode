#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
sqlite_cmd "
create table if not exists file_id_data (
_id integer primary key autoincrement,
_date_create datetime default current_timestamp,
_date_update datetime default current_timestamp,
_file_id integer
);
"
#================================================
