select * from [tablename]
where sortid > (
select sortid from [tablename]
where id = @id
)
