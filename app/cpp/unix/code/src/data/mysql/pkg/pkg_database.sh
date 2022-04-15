#================================================
# pkg_maj
#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_mysql.sh
#================================================
ps_sql "
create database if not exists pad;
create database if not exists dev;
create database if not exists dev01;
create database if not exists dev02;
create database if not exists dev03;
"
#================================================
