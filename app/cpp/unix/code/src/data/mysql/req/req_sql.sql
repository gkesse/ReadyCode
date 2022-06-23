-- ==============================================
-- _maj
-- ==============================================
drop table if exists _maj;

create table if not exists _maj (
    _id int not null auto_increment,
    _code varchar(255) not null,
    _filename varchar(255) not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_code)
);

-- ==============================================
-- user
-- ==============================================
drop table if exists _user;

create table if not exists _user (
    _id int not null auto_increment,
    _email varchar(50),
    _pseudo varchar(50) not null,
    _password varchar(50) not null,
    _group char(1) default '0',
    _active char(1) default '1',
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_pseudo)
);

-- ==============================================
-- _code
-- ==============================================
drop table if exists _code;

create table if not exists _code (
    _id int not null auto_increment,
    _code varchar(50),
    _label varchar(50) not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_code)
);

select * 
from _code
where 1
and _code like lower('%us%')
order by _id desc;

 select _id, _code, _label  
 from _code
 where 1  and _id < 33
order by _id desc
limit 5;

-- ==============================================
-- request
-- ==============================================
drop table if exists _request;

create table if not exists _request (
    _id int not null auto_increment,
    _u_id int not null,
    _module varchar(255) not null,
    _method varchar(255) not null,
    _msg text not null,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_u_id, _module, _method),
    foreign key (_u_id) references _user (_id)
);

-- ==============================================
-- _async
-- ==============================================
drop table if exists _async;

create table if not exists async (
    _id int not null auto_increment,
    _u_id int not null,
    _title varchar(255) not null,
    _status varchar(255) not null,
    _data text,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    foreign key (_u_id) references _user (_id)
);

-- ==============================================
