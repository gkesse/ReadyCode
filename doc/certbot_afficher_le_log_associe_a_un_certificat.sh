# prerequis
->  ready.pad.server doit etre du domain public

# procedure
sudo systemctl stop apache2
sudo certbot --apache -d exemple.com -d www.exemple.com
sudo certbot certonly \
--standalone \
--agree-tos \
--no-eff-email \
-d ready.pad.server

sudo systemctl restart apache2

# affichage du log
sudo cat /var/log/letsencrypt/letsencrypt.log
