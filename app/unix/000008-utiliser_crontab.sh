#================================================
# utiliser_crontab
#================================================

# lister les taches
crontab -l

# ajouter une tache
===> ouvrir l editeur crontab
crontab -e

===> ajouter la ligne
@reboot /home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/scripts/000003-demarrage_serveur_crontab.sh

# supprimer une tache
===> ouvrir l editeur crontab
crontab -e

===> supprimer la ligne
@reboot /home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/scripts/000003-demarrage_serveur_crontab.sh

