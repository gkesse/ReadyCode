
#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_database.sh
#================================================
ps_sql_db $1 "
--
create table if not exists request (
    _id int not null auto_increment,
    _u_id int not null,
    _module varchar(255) not null,
    _method varchar(255) not null,
    _msg blob not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_u_id, _module, _method),
    foreign key (_u_id) references user (_id)
);
--
"
#================================================
