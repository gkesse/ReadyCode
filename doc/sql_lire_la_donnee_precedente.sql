select max(sortid)
from thetable
where sortid < @sortid
