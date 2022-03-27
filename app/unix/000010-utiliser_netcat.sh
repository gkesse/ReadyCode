#================================================
### utiliser_netcat
#================================================

### ressources
http://site.iugaza.edu.ps/hradi/files/Lab-12-NetCat.pdf

### scanner un port
nc -v -w 2 -z 127.0.0.1 3306
==>
Connection to 127.0.0.1 3306 port [tcp/mysql] succeeded!

### scanner une plage de ports
nc -v -w 2 -z 127.0.0.1 9090-9099
==>
Connection to 127.0.0.1 9090 port [tcp/*] succeeded!
nc: connect to 127.0.0.1 port 9091 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9092 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9093 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9094 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9095 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9096 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9097 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9098 (tcp) failed: Connection refused
nc: connect to 127.0.0.1 port 9099 (tcp) failed: Connection refused
