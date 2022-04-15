#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_mysql.sh
#================================================
ps_sql "
--
create database if not exists pad;
create database if not exists dev;
--
"
#================================================
