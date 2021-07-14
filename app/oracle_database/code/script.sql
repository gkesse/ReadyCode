-- ==============================================
set serveroutput on;
-- ==============================================
declare
    type t_stringlist is varray(5) of varchar(10);
    l_digits t_stringlist := t_stringlist('Un', 'Deux', 'Trois', 'Quatre', 'Cinq');
    l_count integer:= l_digits.count;
-- ==============================================
begin
    for i in 1..l_count loop
        dbms_output.put_line(l_digits(i));
    end loop;
end;
/
-- ==============================================
