-- ==============================================
set serveroutput on;
-- ==============================================
declare
    a integer := 22;
    b integer := 7;
-- ==============================================
begin
    dbms_output.put_line(a || ' + ' || b || ' = ' || (a + b));
    dbms_output.put_line(a || ' - ' || b || ' = ' || (a - b));
    dbms_output.put_line(a || ' * ' || b || ' = ' || (a * b));
    dbms_output.put_line(a || ' / ' || b || ' = ' || (a / b));
end;
/
-- ==============================================
