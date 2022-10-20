sudo chmod 777 /etc/apache2/sites-available/000-default.conf
sudo cat << _EOF_ > /etc/apache2/sites-available/000-default.conf
<VirtualHost *:80>
    ServerName readydev.ovh
    ServerAlias www.readydev.ovh 
    ServerAdmin tiakagerard@hotmail.com
    DocumentRoot /home/gkesse/Programs/ReadyDev
    ErrorLog /home/gkesse/Programs/ReadyDev/logs/error.log
    CustomLog /home/gkesse/Programs/ReadyDev/logs/access.log combined
    
    Redirect permanent / https://readydev.ovh/
</VirtualHost>
_EOF_
sudo chmod 644 /etc/apache2/sites-available/000-default.conf
sudo systemctl restart apache2
