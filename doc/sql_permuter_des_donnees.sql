update thetable
set sortid = @sortid1 + @sortid2 - sortid
where sortid in (@sortid1, @sortid2)
