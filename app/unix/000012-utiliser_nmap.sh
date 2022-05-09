#================================================
### utiliser_nmap
#================================================

### ressources
https://github.com/YuxuanLing/books/raw/master/network/Nmap%20Network%20Scanning.pdf

### installer nmap sous ubuntu
sudo apt install nmap

### scanner les ports
nmap -A -T4 127.0.0.1
==>
gkesse@gkesse-desktop:~$ nmap -A -T4 127.0.0.1
Starting Nmap 7.80 ( https://nmap.org ) at 2022-03-27 11:15 CEST
Nmap scan report for localhost (127.0.0.1)
Host is up (0.00065s latency).
Not shown: 996 closed ports
PORT     STATE SERVICE       VERSION
22/tcp   open  ssh           OpenSSH 8.4p1 Ubuntu 6ubuntu2.1 (Ubuntu Linux; protocol 2.0)
631/tcp  open  ipp           CUPS 2.3
| http-robots.txt: 1 disallowed entry
|_/
|_http-server-header: CUPS/2.3 IPP/2.1
|_http-title: Home - CUPS 2.3.3op2
3306/tcp open  nagios-nsca   Nagios NSCA
| mysql-info:
|   Protocol: 10
|   Version: 8.0.28-0ubuntu0.21.10.3
|   Thread ID: 14
|   Capabilities flags: 65535
|   Some Capabilities: DontAllowDatabaseTableColumn, FoundRows, Speaks41ProtocolNew, IgnoreSpaceBeforeParenthesis, SupportsCompression, Support41Auth, IgnoreSigpipes, ODBCClient, SupportsLoadDataLocal, Speaks41ProtocolOld, LongColumnFlag, LongPassword, ConnectWithDatabase, SupportsTransactions, SwitchToSSLAfterHandshake, InteractiveClient, SupportsMultipleStatments, SupportsAuthPlugins, SupportsMultipleResults
|   Status: Autocommit
|   Salt: \x01^W\x13G\x02\x12kblGwZ*N\x18]C()
|_  Auth Plugin Name: caching_sha2_password
3389/tcp open  ms-wbt-server xrdp
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 73.17 seconds
