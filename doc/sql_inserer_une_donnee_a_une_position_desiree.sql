-- pour incrementer les positions suivantes
update your_table
set sortid = sortid + 1
where sortid >= 10;

-- pour insérer la donnée à la position désirée
insert into your_table (..., sortid) 
values (..., 10);
