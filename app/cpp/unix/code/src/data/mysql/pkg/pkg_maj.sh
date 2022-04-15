#!/bin/bash
#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_mysql.sh
. $GPKG/pkg_database.sh
#================================================
ps_sql_db $1 "
--
create table if not exists maj (
    _id int not null auto_increment,
    _code varchar(6) not null,
    _filename varchar(255) not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_code)
);
--
"
#================================================
