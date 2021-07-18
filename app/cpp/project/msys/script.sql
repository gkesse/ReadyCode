select count(*) as _count
from pragma_table_info('users')
where name = 'username';
