# configurer le proxy ssh
onglet -> ssh
cocher -> utiliser tunnel ssh
hote ip -> 192.168.1.45
port -> 22
nom utilisateur -> gkesse
methode authentification -> mot de passe
mot de passe -> GKESSE_PASSWORD
tester tunnel configuration
ok

# creer un profil ssh
profil
create
NOM_PROFIL
ok
appliquer et fermer

# configurer la connexion au serveur
onglet -> general
server host -> localhost
port -> 3306
nom utilisateur -> admin
mot de passe -> MYSQL_PASSWORD
server timezone -> auto-detect
local client -> mysql binaries
tester connexion
ok
