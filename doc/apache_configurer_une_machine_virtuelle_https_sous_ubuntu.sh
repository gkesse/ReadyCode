sudo chmod 777 /etc/apache2/sites-available/000-default-le-ssl.conf
sudo cat << _EOF_ > /etc/apache2/sites-available/000-default-le-ssl.conf
<IfModule mod_ssl.c>
    <VirtualHost *:443>
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
        
        SSLEngine on
        SSLCertificateFile  /etc/letsencrypt/live/readydev.ovh/cert.pem
        SSLCertificateKeyFile   /etc/letsencrypt/live/readydev.ovh/privkey.pem
        SSLCertificateChainFile  /etc/letsencrypt/live/readydev.ovh/chain.pem
        
        SSLProtocol all -SSLv2 -SSLv3
        SSLCipherSuite ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-AES256-SHA:DHE-RSA-AES256-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:AES:CAMELLIA:DES-CBC3-SHA:!aNULL:!eNULL:!EXPORT:!DES:!RC4:!MD5:!PSK:!aECDH:!EDH-DSS-DES-CBC3-SHA:!EDH-RSA-DES-CBC3-SHA:!KRB5-DES-CBC3-SHA
        SSLHonorCipherOrder on
        SSLCompression off
        SSLOptions +StrictRequire
        
        Header always set Strict-Transport-Security "max-age=15768000"
    </VirtualHost>
</IfModule>
_EOF_
sudo chmod 644 /etc/apache2/sites-available/000-default-le-ssl.conf
sudo systemctl restart apache2
