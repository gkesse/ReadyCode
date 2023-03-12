-- ==============================================
-- database
-- ==============================================
use dev;

-- ==============================================
-- _site
-- ==============================================
drop table if exists _site;

insert into _site (_id, _name, _title, _label)
values (1, 'readydev', 'ReadyDev', 'Plateforme de Développement en Continu');
insert into _site (_id, _name, _title, _label)
values (2, 'readycar', 'ReadyCar', 'Plateforme de Covoiturage en Continu');
insert into _site (_id, _name, _title, _label)
values (3, 'readyevent', 'ReadyEvent', 'Plateforme de l''Evènementiel en Continu');
insert into _site (_id, _name, _title, _label)
values (4, 'readyshop', 'ReadyShop', 'Plateforme de eCommerce en Continu');
insert into _site (_id, _name, _title, _label)
values (5, 'readyharriste', 'Harriste', 'Eglise Harriste de France de Côte d''Ivoire');

create table if not exists _site (
    _id int not null auto_increment
    , _name varchar(255) not null
    , _title varchar(255)
    , _label varchar(255)
    , _create_date datetime default current_timestamp
    , _update_date datetime on update current_timestamp
    , primary key (_id)
    , unique (_name)
);

-- ==============================================
-- _page
-- ==============================================
drop table if exists _page;

insert into _page (_id, _name, _type_id)
values (1, 'root', 2);

create table if not exists _page (
    _id int not null auto_increment
    , _parent_id int
    , _site_id int not null
    , _type_id int not null
    , _name varchar(255) not null
    , _path varchar(255)
    , _id_path varchar(255)
    , _is_default char(1) default '0'
    , _create_date datetime default current_timestamp
    , _update_date datetime on update current_timestamp
    , primary key (_id)
    , unique (_parent_id, _name)
    , foreign key (_parent_id) references _page (_id)    
    , foreign key (_type_id) references _page_type (_id)    
);

alter table _page add column _default char(1) default '0';

-- ==============================================
-- _page_type
-- ==============================================
drop table if exists _page_type;

insert into _page_type (_id, _name, _label) values
(1, 'file', 'Fichier')
, (2, 'dir', 'Répertoire');

create table if not exists _page_type (
    _id int not null auto_increment
    , _name varchar(255) not null
    , _label varchar(255) not null
    , _c_date datetime default current_timestamp
    , _u_date datetime on update current_timestamp
    , primary key (_id)
);

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
-- _file
-- ==============================================
drop table if exists _file;

create table if not exists _file (
    _id int not null auto_increment,
    _filename varchar(255) not null,
    _fullname varchar(255),
    _create_date datetime default current_timestamp,
    _upadte_date datetime on update current_timestamp,
    primary key (_id)
);

-- ==============================================
-- _module
-- ==============================================
drop table if exists _module;

create table if not exists _module (
    _id int not null auto_increment,
    _name varchar(255) not null,
    _create_date datetime default current_timestamp,
    _upadte_date datetime on update current_timestamp,
    primary key (_id),
    unique(_name)
);

-- ==============================================
-- _module_data
-- ==============================================
drop table if exists _module_data;

create table if not exists _module_data (
      _id int not null auto_increment
    , _module_id int not null
    , _name varchar(255) not null
    , _value varchar(255)
    , _create_date datetime default current_timestamp
    , _upadte_date datetime on update current_timestamp
    , primary key (_id)
    , unique(_module_id, _name)
    , foreign key (_module_id) references _module (_id)
);

-- ==============================================
-- _module_key
-- ==============================================
drop table if exists _module_key;

create table if not exists _module_key (
      _id int not null auto_increment
    , _module_id int not null
    , _type_id int not null
    , _name varchar(255) not null
    , _label varchar(255) not null
    , _create_date datetime default current_timestamp
    , _upadte_date datetime on update current_timestamp
    , primary key (_id)
    , unique(_module_id, _name)
    , foreign key (_module_id) references _module (_id)
    , foreign key (_type_id) references _module_type (_id)
);

-- ==============================================
-- _module_map
-- ==============================================
drop table if exists _module_map;

create table if not exists _module_map (
      _id int not null auto_increment
    , _module_id int not null
    , _position int not null
    , _create_date datetime default current_timestamp
    , _upadte_date datetime on update current_timestamp
    , primary key (_id)
    , foreign key (_module_id) references _module (_id)
);

select (max(_position) + 1) from _module_map;

-- ==============================================
-- _module_node
-- ==============================================
drop table if exists _module_node;

create table if not exists _module_node (
      _id int not null auto_increment
    , _module_id int not null
    , _map_id int not null
    , _key_id int not null
    , _value varchar(255) not null
    , _create_date datetime default current_timestamp
    , _upadte_date datetime on update current_timestamp
    , primary key (_id)
    , unique(_module_id, _map_id, _key_id)
    , foreign key (_module_id) references _module (_id)
    , foreign key (_map_id) references _module_map (_id)
    , foreign key (_key_id) references _module_key (_id)
);

-- ==============================================
-- _module_type
-- ==============================================
drop table if exists _module_type;

create table if not exists _module_type (
    _id int not null auto_increment,
    _name varchar(255) not null,
    _create_date datetime default current_timestamp,
    _upadte_date datetime on update current_timestamp,
    primary key (_id),
    unique(_name)
);

-- ==============================================
-- _query_type
-- ==============================================
drop table if exists _query_type;

create table if not exists _query_type (
    _id int not null auto_increment,
    _name varchar(255) not null,
    _default char(1) default '0',
    _create_date datetime default current_timestamp,
    _upadte_date datetime on update current_timestamp,
    primary key (_id),
    unique(_name)
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
    _connect char(1) default '0',
    _d_connect datetime,
    _c_date datetime default current_timestamp,
    _u_date datetime on update current_timestamp,
    primary key (_id),
    unique (_pseudo)
);

-- ==============================================
-- group
-- ==============================================
drop table if exists _group;

create table if not exists _group (
    _id int not null auto_increment,
    _group varchar(50) not null,
    primary key (_id),
    unique (_group)
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

