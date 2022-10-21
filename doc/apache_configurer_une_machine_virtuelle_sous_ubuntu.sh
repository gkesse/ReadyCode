sudo nano /etc/apache2/sites-available/000-default.conf

<VirtualHost *:8001>
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

sudo systemctl restart apache2

