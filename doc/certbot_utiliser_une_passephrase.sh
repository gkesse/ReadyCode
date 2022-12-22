https://community.letsencrypt.org/t/is-the-generated-certificate-password-protected/23402

impossible

Le certificat généré par Certbot et utilisé par votre serveur Web 
n''est pas protégé par un mot de passe - 
il ne contient que du matériel non secret et peut être largement partagé

La clé privée générée par Certbot qui accompagne le certificat n''est pas 
non plus protégée par un mot de passe. Il est protégé uniquement 
par les autorisations du système de fichiers et ne doit pas être partagé .

