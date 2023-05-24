https://www.youtube.com/watch?v=_cSQKOajwlA
https://www.php.net/manual/en/ini.core.php#ini.zend-extension
https://xdebug.org/docs/all_settings#mode

[xdebug]
zend_extension="C:\wamp64\v3.3.0\bin\php\php8.0.26\ext\php_xdebug.dll"
xdebug.mode=debug
xdebug.client_host=localhost
xdebug.client_port=9003

[xdebug]
zend_extension="c:/wamp64/v3.3.0/bin/php/php8.0.26/zend_ext/php_xdebug-3.1.6-8.0-vs16-x86_64.dll"
;xdebug.mode allowed are : off develop coverage debug gcstats profile trace
xdebug.mode =develop
xdebug.output_dir ="c:/wamp64/v3.3.0/tmp"
xdebug.show_local_vars=0
xdebug.log="c:/wamp64/v3.3.0/logs/xdebug.log"
;xdebug.log_level : 0 Criticals, 1 Connection, 3 Warnings, 5 Communication, 7 Information, 10 Debug	Breakpoint
xdebug.log_level=7
xdebug.profiler_output_name=trace.%H.%t.%p.cgrind
xdebug.use_compression=false

zend_extension="C:\wamp64\v3.3.0\bin\php\php8.0.26\ext\php_xdebug.dll"
Nom de l'extension Zend chargeable dynamiquement (par exemple XDebug)
à charger au démarrage de PHP.

xdebug.mode=debug
Active le débogage des étapes.
Cela peut être utilisé pour parcourir votre code pendant son exécution
et analyser les valeurs des variables.

xdebug.client_host=127.0.0.1
Configure l'adresse IP ou le nom d'hôte auquel Xdebug
tentera de se connecter lors de l'initialisation d'une connexion de débogage.
Cette adresse doit être l'adresse de la machine sur laquelle
votre IDE ou client de débogage écoute les connexions de débogage entrantes.

xdebug.client_port=9001
Le port auquel Xdebug essaie de se connecter sur l'hôte distant.
Le port 9003est la valeur par défaut pour Xdebug
et le client de débogage de ligne de commande.
Comme de nombreux clients utilisent ce numéro de port,
il est préférable de laisser ce paramètre inchangé.
