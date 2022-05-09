#================================================
# operations_ports_ubuntu
#================================================

# lister les ports
sudo lsof -i -P -n | grep LISTEN

systemd-r   713 systemd-resolve   14u  IPv4  20666      0t0  TCP 127.0.0.53:53 (LISTEN)
cupsd       864            root    6u  IPv6  24007      0t0  TCP [::1]:631 (LISTEN)
cupsd       864            root    7u  IPv4  24008      0t0  TCP 127.0.0.1:631 (LISTEN)
xrdp-sesm   893            root    7u  IPv6  23798      0t0  TCP [::1]:3350 (LISTEN)
sshd        922            root    3u  IPv4  23825      0t0  TCP *:22 (LISTEN)
sshd        922            root    4u  IPv6  23827      0t0  TCP *:22 (LISTEN)
xrdp        937            xrdp   11u  IPv6  21283      0t0  TCP *:3389 (LISTEN)
mysqld      979           mysql   22u  IPv4  21439      0t0  TCP 127.0.0.1:33060 (LISTEN)
mysqld      979           mysql   34u  IPv4  23040      0t0  TCP 127.0.0.1:3306 (LISTEN)
sshd      12121          gkesse   10u  IPv6  44478      0t0  TCP [::1]:6010 (LISTEN)
sshd      12121          gkesse   11u  IPv4  44479      0t0  TCP 127.0.0.1:6010 (LISTEN)

# lister les ports
sudo ss -tulpn | grep LISTEN

tcp   LISTEN 0      4096   127.0.0.53%lo:53         0.0.0.0:*    users:(("systemd-resolve",pid=713,fd=14))
tcp   LISTEN 0      128          0.0.0.0:22         0.0.0.0:*    users:(("sshd",pid=922,fd=3))
tcp   LISTEN 0      128        127.0.0.1:631        0.0.0.0:*    users:(("cupsd",pid=864,fd=7))
tcp   LISTEN 0      128        127.0.0.1:6010       0.0.0.0:*    users:(("sshd",pid=12121,fd=11))
tcp   LISTEN 0      70         127.0.0.1:33060      0.0.0.0:*    users:(("mysqld",pid=979,fd=22))
tcp   LISTEN 0      151        127.0.0.1:3306       0.0.0.0:*    users:(("mysqld",pid=979,fd=34))
tcp   LISTEN 0      128             [::]:22            [::]:*    users:(("sshd",pid=922,fd=4))
tcp   LISTEN 0      2              [::1]:3350          [::]:*    users:(("xrdp-sesman",pid=893,fd=7))
tcp   LISTEN 0      128            [::1]:631           [::]:*    users:(("cupsd",pid=864,fd=6))
tcp   LISTEN 0      128            [::1]:6010          [::]:*    users:(("sshd",pid=12121,fd=10))
tcp   LISTEN 0      2                  *:3389             *:*    users:(("xrdp",pid=937,fd=11))

# afficher l'application utilisant un port specifique
sudo lsof -i:22

COMMAND   PID   USER   FD   TYPE DEVICE SIZE/OFF NODE NAME
sshd      922   root    3u  IPv4  23825      0t0  TCP *:ssh (LISTEN)
sshd      922   root    4u  IPv6  23827      0t0  TCP *:ssh (LISTEN)
sshd    11914   root    4u  IPv4  42467      0t0  TCP gkesse-desktop:ssh->192.168.1.39:64840 (ESTABLISHED)
sshd    11916   root    4u  IPv4  43209      0t0  TCP gkesse-desktop:ssh->192.168.1.39:64843 (ESTABLISHED)
sshd    12091 gkesse    4u  IPv4  43209      0t0  TCP gkesse-desktop:ssh->192.168.1.39:64843 (ESTABLISHED)
sshd    12121 gkesse    4u  IPv4  42467      0t0  TCP gkesse-desktop:ssh->192.168.1.39:64840 (ESTABLISHED)

# lister les ports
ss -tulw

Netid          State           Recv-Q           Send-Q                     Local Address:Port                              Peer Address:Port          Process
icmp6          UNCONN          0                0                                      *:ipv6-icmp                                    *:*
udp            UNCONN          0                0                                0.0.0.0:631                                    0.0.0.0:*
udp            UNCONN          0                0                                0.0.0.0:mdns                                   0.0.0.0:*
udp            UNCONN          0                0                                0.0.0.0:36756                                  0.0.0.0:*
udp            UNCONN          0                0                          127.0.0.53%lo:domain                                 0.0.0.0:*
udp            UNCONN          0                0                                   [::]:33320                                     [::]:*
udp            UNCONN          0                0                                   [::]:mdns                                      [::]:*
tcp            LISTEN          0                4096                       127.0.0.53%lo:domain                                 0.0.0.0:*
tcp            LISTEN          0                128                              0.0.0.0:ssh                                    0.0.0.0:*
tcp            LISTEN          0                128                            127.0.0.1:ipp                                    0.0.0.0:*
tcp            LISTEN          0                128                            127.0.0.1:6010                                   0.0.0.0:*
tcp            LISTEN          0                70                             127.0.0.1:33060                                  0.0.0.0:*
tcp            LISTEN          0                151                            127.0.0.1:mysql                                  0.0.0.0:*
tcp            LISTEN          0                128                                 [::]:ssh                                       [::]:*
tcp            LISTEN          0                2                                  [::1]:3350                                      [::]:*
tcp            LISTEN          0                128                                [::1]:ipp                                       [::]:*
tcp            LISTEN          0                128                                [::1]:6010                                      [::]:*
tcp            LISTEN          0                2                                      *:ms-wbt-server                                *:*

# afficher les services reseaux et numeros de ports
less /etc/services

tcpmux          1/tcp                           # TCP port service multiplexer
echo            7/tcp
echo            7/udp
discard         9/tcp           sink null
discard         9/udp           sink null
systat          11/tcp          users
daytime         13/tcp
daytime         13/udp
netstat         15/tcp
qotd            17/tcp          quote
chargen         19/tcp          ttytst source
chargen         19/udp          ttytst source
ftp-data        20/tcp
ftp             21/tcp
fsp             21/udp          fspd
ssh             22/tcp                          # SSH Remote Login Protocol
telnet          23/tcp
smtp            25/tcp          mail
time            37/tcp          timserver
time            37/udp          timserver
whois           43/tcp          nicname
tacacs          49/tcp                          # Login Host Protocol (TACACS)
tacacs          49/udp
domain          53/tcp                          # Domain Name Server
domain          53/udp
bootps          67/udp
bootpc          68/udp
tftp            69/udp
gopher          70/tcp                          # Internet Gopher
finger          79/tcp
http            80/tcp          www             # WorldWideWeb HTTP
kerberos        88/tcp          kerberos5 krb5 kerberos-sec     # Kerberos v5
kerberos        88/udp          kerberos5 krb5 kerberos-sec     # Kerberos v5
iso-tsap        102/tcp         tsap            # part of ISODE
acr-nema        104/tcp         dicom           # Digital Imag. & Comm. 300
:
