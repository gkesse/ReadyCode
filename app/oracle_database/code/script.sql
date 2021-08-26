-- ==============================================
create package pkg_fnc_hello as
    function fnc_hello return varchar2;
end pkg_fnc_hello;
/
-- ==============================================
create package pkg_fnc_hello as
    function fnc_hello return varchar2;
    function fnc_hello(name in varchar2) return varchar2;
end pkg_fnc_hello;
/
-- ==============================================
create package pkg_prc_hello as
    procedure prc_hello;
    procedure prc_hello(name in varchar2);
end pkg_prc_hello;
/
-- ==============================================
drop package pkg_fnc_hello;
-- ==============================================
drop package pkg_prc_hello;
-- ==============================================
select count(*)
from user_objects
where object_name = upper('pkg_fnc_hello')
and object_type = upper('package');
-- ==============================================
create or replace package body pkg_fnc_hello as
    function fnc_hello return varchar2 is 
    begin
        return 'Bonjour tout le monde';
    end fnc_hello;
end pkg_fnc_hello;
/
-- ==============================================
create or replace package body pkg_fnc_hello as
    function fnc_hello return varchar2 is 
    begin
        return 'Bonjour tout le monde';
    end fnc_hello;
    -- ==============================================
    function fnc_hello(name in varchar2) return varchar2 is 
    begin
        return 'Bonjour ' || name;
    end fnc_hello;
end pkg_fnc_hello;
/
-- ==============================================
create or replace package body pkg_prc_hello as
    procedure prc_hello is 
    begin
        dbms_output.put_line('Bonjour tout le monde');
    end prc_hello;
    -- ==============================================
    procedure prc_hello(name in varchar2) is 
    begin
        dbms_output.put_line('Bonjour ' || name);
    end prc_hello;
end pkg_prc_hello;
/
-- ==============================================
begin 
    dbms_output.put_line(pkg_fnc_hello.fnc_hello); 
end;
/
-- ==============================================
begin 
    pkg_prc_hello.prc_hello; 
    pkg_prc_hello.prc_hello('Gerard KESSE'); 
end;
/
-- ==============================================
