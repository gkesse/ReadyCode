-- on incrémente les positions suivantes
update your_table
set sortid = sortid + 1
where sortid >= 10;

-- on insère la donnee à la position désirée
insert into your_table (..., sortid) 
values (..., 10);
