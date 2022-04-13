#================================================
# pkg_maj
#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_mysql.sh
#================================================
ps_sql "
select 'Bonjour tout le monde';
select 'Bonjour tout le monde';
"
#================================================

