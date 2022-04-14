#================================================
# pkg_mysql
#================================================
GCONFIG=$GCONF/pkg_config.cnf
#================================================
ps_sql() {
    mysql --defaults-extra-file=$GCONFIG -Bse "$2"
}
#================================================
ps_sql_db() {
    mysql --defaults-extra-file=$GCONFIG $1 -Bse "$2"
}
#================================================
