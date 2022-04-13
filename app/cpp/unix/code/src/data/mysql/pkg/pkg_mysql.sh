#================================================
# pkg_mysql
#================================================
GUSER=admin
GPASSWORD=xKCQY7GiGTVJ4l334QxN87@TKg
#================================================
sql_query() {
mysql -u$GUSER -p$GPASSWORD << _EOF_
select "Bonjour tout le monde";
select "Bonjour tout le monde";
_EOF_
}
