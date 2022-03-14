#================================================
# operations_ports_ubuntu
#================================================

# liens
https://linuxize.com/post/how-to-setup-a-firewall-with-ufw-on-ubuntu-18-04/

# installer le pare-feu
sudo apt install ufw

Construction de l arbre des dépendances... Fait
Lecture des informations d état... Fait
ufw est déjà la version la plus récente (0.36.1-1ubuntu1).
ufw passé en « installé manuellement ».
Le paquet suivant a été installé automatiquement et n est plus nécessaire :
  libfwupdplugin1
Veuillez utiliser « sudo apt autoremove » pour le supprimer.
0 mis à jour, 0 nouvellement installés, 0 à enlever et 0 non mis à jour.

# verifier l'etat du pare-feu
sudo ufw status verbose

Status: inactive

# lister tous les profils d'application disponibles
sudo ufw app list

Available applications:
  CUPS
  OpenSSH

