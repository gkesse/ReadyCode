#================================================
. $GPROJECT_DATA/mysql/pkg/pkg_var.sh
. $GPKG/pkg_database.sh
#================================================
ps_sql_db $1 "
--
create table if not exists async (
    _id int not null auto_increment,
    _u_id int not null,
    _title varchar(255) not null,
    _status varchar(255) not null,
    _data text,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    foreign key (_u_id) references user (_id)
);
--
"
#================================================
