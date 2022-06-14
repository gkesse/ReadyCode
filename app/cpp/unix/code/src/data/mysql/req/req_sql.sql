-- ==============================================
-- maj
-- ==============================================
select *
from maj m
order by m._id;

-- ==============================================
-- user
-- ==============================================
create table if not exists user_mode (
    _id int not null auto_increment,
    _pseudo varchar(255) not null,
    _password varchar(255) not null,
    _group char(1) default '2',
    _active char(1) default '1',
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_pseudo)
);

-- ==============================================
