ouvrir -> C:\wamp64\bin\apache\apache2.4.51\conf\extra\httpd-vhosts.conf

<VirtualHost *:8001>
    ServerName readydev.ovh
    ServerAlias www.readydev.ovh 
    ServerAdmin tiakagerard@hotmail.com
    DocumentRoot C:\Users\tiaka\Downloads\eTools\ePrograms\ReadyDev
    ErrorLog C:\Users\tiaka\Downloads\eTools\ePrograms\ReadyDev/logs/error.log
    CustomLog C:\Users\tiaka\Downloads\eTools\ePrograms\ReadyDev/logs/access.log combined

    SetEnv GPROJECT_ENV "TEST"

    <Directory C:\Users\tiaka\Downloads\eTools\ePrograms\ReadyDev>
        Options All
        AllowOverride All
        Order allow,deny
        allow from all
        Require all granted
    </Directory>
</VirtualHost>

redemarrer -> wampserver
