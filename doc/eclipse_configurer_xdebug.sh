window
preferences
php
add
name -> php_xdebug
executable path -> C:\wamp64\bin\php\php7.4.26\php.exe
php in file (optional) -> C:\wamp64\bin\php\php7.4.26\php.ini
sapi -> cli
next
debugger -> xdebug
port -> 7001
finish

debug as
debug configurations
php web application
clic droit
new configuration
name -> php_xdebug_config
apply

server
php server
server name -> Default PHP Web Server
configure
base url -> http://localhost:8001/
document root -> C:\Users\tiaka\Downloads\eTools\ePrograms\ReadyDev
finish

server
file
browse
rphp_dev -> index.php
url
decocher -> auto generate
url -> http://localhost:8001/ -> /index.php
apply

debugger
configure
debugger -> xdebug
port -> 7001
finish
