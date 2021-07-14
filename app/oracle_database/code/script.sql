-- ==============================================
set serveroutput on;
-- ==============================================
declare
    a boolean := true;
    b boolean := false;
-- ==============================================
begin
    dbms_output.put_line('!' || sys.diutil.bool_to_int(a) || ' = ' || sys.diutil.bool_to_int(not(a)));
    dbms_output.put_line('!' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(not(b)));
    dbms_output.put_line(sys.diutil.bool_to_int(a) || ' || ' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(a or b));
    dbms_output.put_line(sys.diutil.bool_to_int(a) || ' || ' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(a or b));
    dbms_output.put_line(sys.diutil.bool_to_int(b) || ' || ' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(b or b));
    dbms_output.put_line(sys.diutil.bool_to_int(a) || ' || ' || sys.diutil.bool_to_int(a) || ' = ' || sys.diutil.bool_to_int(a or a));
    dbms_output.put_line(sys.diutil.bool_to_int(a) || ' && ' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(a and b));
    dbms_output.put_line(sys.diutil.bool_to_int(b) || ' && ' || sys.diutil.bool_to_int(b) || ' = ' || sys.diutil.bool_to_int(b and b));
    dbms_output.put_line(sys.diutil.bool_to_int(a) || ' && ' || sys.diutil.bool_to_int(a) || ' = ' || sys.diutil.bool_to_int(a and a));
end;
/
-- ==============================================
