#================================================
# pkg_maj
#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_mysql.sh
#================================================
ps_sql "
--
create table if not exists maj (
    _id int not null,
    _code varchar(6) not null,
    _filename varchar(255) not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp
);
--
alter table maj
add constraint pk_maj primary key (_id);
--
alter table maj
add constraint uc_maj unique (_code);
--
"
#================================================

