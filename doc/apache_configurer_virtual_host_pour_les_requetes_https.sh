php --version

sudo a2enmod ssl
sudo systemctl restart apache2

sudo a2enmod headers
sudo systemctl restart apache2

sudo chmod 777 /etc/apache2/sites-available/000-default.conf
sudo cat << _EOF_ > /etc/apache2/sites-available/000-default.conf
<VirtualHost *:80>
    ServerName readydev.ovh
    ServerAlias www.readydev.ovh 
    ServerAdmin tiakagerard@hotmail.com
    DocumentRoot /home/gkesse/Programs/ReadyDev
    ErrorLog /home/gkesse/Programs/ReadyDev/logs/error.log
    CustomLog /home/gkesse/Programs/ReadyDev/logs/access.log combined

    <Directory /home/gkesse/Programs/ReadyDev>
        Options All
        AllowOverride All
        Order allow,deny
        allow from all
        Require all granted
    </Directory>
</VirtualHost>
_EOF_
sudo chmod 644 /etc/apache2/sites-available/000-default.conf
sudo systemctl restart apache2

sudo chmod 777 /etc/apache2/sites-available/000-default-le-ssl.conf
sudo cat << _EOF_ > /etc/apache2/sites-available/000-default-le-ssl.conf
<IfModule mod_ssl.c>
    <VirtualHost *:443>
        ServerAdmin tiakagerard@hotmail.com
        ServerName readydev.ovh
        ServerAlias www.readydev.ovh    
        DocumentRoot /home/gkesse/Programs/ReadyDev
        ErrorLog /home/gkesse/Programs/ReadyDev/logs/error.log
        CustomLog /home/gkesse/Programs/ReadyDev/logs/access.log combined

        Include /etc/letsencrypt/options-ssl-apache.conf
        SSLCertificateFile /etc/letsencrypt/live/readydev.ovh/fullchain.pem
        SSLCertificateKeyFile /etc/letsencrypt/live/readydev.ovh/privkey.pem
        
        <Directory /home/gkesse/Programs/ReadyDev>
            Options All
            AllowOverride All
            Order allow,deny
            allow from all
            Require all granted
        </Directory>
    </VirtualHost>
</IfModule>
_EOF_
sudo chmod 644 /etc/apache2/sites-available/000-default-le-ssl.conf
sudo systemctl restart apache2
