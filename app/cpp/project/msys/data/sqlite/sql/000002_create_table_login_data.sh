#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
sqlite_cmd "
create table login_data (
_id integer primary key autoincrement,
_date_create datetime default current_timestamp,
_date_update datetime default current_timestamp,
_user_id integer,
_login char(1),
foreign key (_user_id) references user_data (_id)
);
"
#================================================
