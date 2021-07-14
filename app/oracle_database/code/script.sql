-- ==============================================
set serveroutput on;
-- ==============================================
begin
    dbms_output.put_line(utl_lms.format_message('%s : %s : ', 'Nom', 'Gerard KESSE'));
    dbms_output.put_line(utl_lms.format_message('%s : %d : ', 'Identifiant', 123456));
end;
/
-- ==============================================
