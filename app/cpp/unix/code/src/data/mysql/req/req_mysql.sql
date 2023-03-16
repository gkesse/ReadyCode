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
    _id int not null auto_increment -- identifiant du site
    , _name varchar(255) not null -- nom du site
    , _title varchar(255) not null -- titre du site
    , _label varchar(255) not null -- libellé du site
    , _create_date datetime default current_timestamp -- date de création du site
    , _update_date datetime on update current_timestamp -- date de modification du site
    , primary key (_id) -- clé primaire du site
    , unique (_name) -- unicité du site
);

-- ==============================================
-- _page
-- ==============================================
drop table if exists _page;

insert into _page (_id, _name, _type_id, _site_id, _is_root)
values (1, 'root', 2, 1, '1');
insert into _page (_id, _name, _type_id, _site_id, _is_root)
values (2, 'root', 2, 2, '1');
insert into _page (_id, _name, _type_id, _site_id, _is_root)
values (3, 'root', 2, 3, '1');
insert into _page (_id, _name, _type_id, _site_id, _is_root)
values (4, 'root', 2, 4, '1');
insert into _page (_id, _name, _type_id, _site_id, _is_root)
values (5, 'root', 2, 5, '1');

create table if not exists _page (
    _id int not null auto_increment -- identifiant de la page
    , _parent_id int -- identifiant du parent de la page
    , _site_id int not null -- identifiant du site de la page
    , _type_id int not null -- identifiant du type de la page ? (1=fichier ; 2=répertoire)
    , _name varchar(255) not null -- nom de la page
    , _path varchar(255) -- chemin de la page
    , _id_path varchar(255) -- chemin des ids des parents de la page
    , _is_default char(1) default '0' -- page par défaut ? (0=non; 1=oui)
    , _is_root char(1) default '0' -- page racine ? (0=non; 1=oui)
    , _create_date datetime default current_timestamp -- date de création de la page
    , _update_date datetime on update current_timestamp -- date de modification de la page
    , primary key (_id) -- clé primaire de la page
    , unique (_parent_id, _site_id, _name) -- unicité de la page
    , foreign key (_parent_id) references _page (_id) -- contrainte sur le parent de la page
    , foreign key (_type_id) references _page_type (_id) -- contrainte sur le type de la page
    , foreign key (_site_id) references _site (_id) -- contrainte sur le site de la page
);

alter table _page add column _default char(1) default '0';

-- ==============================================
-- _page_type
-- ==============================================
drop table if exists _page_type;

insert into _page_type (_id, _name, _label)
values (1, 'file', 'Fichier');
insert into _page_type (_id, _name, _label)
values (2, 'dir', 'Répertoire');

create table if not exists _page_type (
    _id int not null auto_increment -- identifiant du type de la page
    , _name varchar(255) not null -- nom du type de la page
    , _label varchar(255) not null -- libellé du type de la page
    , _create_date datetime default current_timestamp -- date de création du type de la page
    , _update_date datetime on update current_timestamp -- date de modification du type de la page
    , primary key (_id) -- clé primaire du type de la page
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

