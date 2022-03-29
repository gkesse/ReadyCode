#================================================
# utiliser_sysctl
#================================================

# ressources
https://stackoverflow.com/questions/7865069/how-to-find-the-socket-buffer-size-of-linux

# lire taille memoire lecture/ecriture
cat /proc/sys/net/ipv4/tcp_rmem
cat /proc/sys/net/ipv4/tcp_wmem

# lire taille memoire lecture/ecriture
cat /proc/sys/net/core/rmem_default
cat /proc/sys/net/core/wmem_default

# lire taille memoire lecture/ecriture
sysctl net.ipv4.tcp_rmem
sysctl net.ipv4.tcp_wmem

# lire taille memoire lecture/ecriture
ss -tm

# lire taille memoire c/c++
int n;
unsigned int m = sizeof(n);
int fdsocket;
fdsocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
getsockopt(fdsocket,SOL_SOCKET,SO_RCVBUF,(void *)&n, &m);
