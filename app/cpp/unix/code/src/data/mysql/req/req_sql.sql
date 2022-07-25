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
    _pseudo varchar(50) not null,
    _password varchar(50) not null,
    _email varchar(50),
    _group varchar(50) default 'user',
    _active char(1) default '1',
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_pseudo)
);

insert into _user  ( _pseudo, _password )  values ( 'gkesse', '613e1c1180be8c92bc3a6cad00c113d5' );

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

select _id 
from _code
where 1  
order by _id desc
limit 1;

select _id, _code, _label  
from _code
where 1  
and _id > 26
order by _id
limit 5;

select _id, _code, _label  
from _code
where 1  
and _id < 34
order by _id desc
limit 5;

select _id, _code, _label  
from _code
where 1  
order by _id desc
limit 5 offset 0;

delete from _code
where _id = 27;

update _code
set _label = 'label_moto'
where _id = 26;

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
