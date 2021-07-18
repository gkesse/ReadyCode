#================================================
function sqlite_cmd() {
sqlite3 $GSQLITE_DB_PATH << _EOF_
$1
_EOF_
}
#================================================
lCount=$(
sqlite_cmd "
select count(*) from sqlite_master
where type = 'table'
and  name = 'users';
")
#================================================
if [ "$lCount" == "1" ] ; then
sqlite_cmd "
alter table users
rename to user_data;
"
fi
#================================================
lCount=$(
sqlite_cmd "
select count(*) from sqlite_master
where type = 'table'
and  name = 'login';
")
#================================================
if [ "$lCount" = "1" ] ; then
sqlite_cmd "
alter table login
rename to login_data;
"
fi
#================================================
