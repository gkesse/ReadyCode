https://www.digitalocean.com/community/tutorials/how-to-secure-apache-with-let-s-encrypt-on-ubuntu-18-04

# prerequis
->  ready.pad.server doit etre du domain public

# procedure
sudo systemctl stop apache2

sudo certbot certonly \
--standalone \
--agree-tos \
--no-eff-email \
-d readydev.ovh \
-d www.readydev.ovh \

sudo systemctl restart apache2

# affichage du log
sudo cat /var/log/letsencrypt/letsencrypt.log
