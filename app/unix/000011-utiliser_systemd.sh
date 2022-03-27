#================================================
# utiliser_systemd
#================================================

# ressources
https://medium.com/@benmorel/creating-a-linux-service-with-systemd-611b5c8b91d6

# configurer un service
===> ouvrir le service
nano /etc/systemd/system/pad.service

===> configurer le service
[Unit]
Description=pad service
After=network.target
StartLimitIntervalSec=0

[Service]
Type=simple
Restart=always
RestartSec=1
User=gkesse
ExecStart=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/scripts/000003-demarrage_serveur_crontab.sh

[Install]
WantedBy=multi-user.target

===> demarrer le service
sudo systemctl start pad

===> demarrer le service au redemarrage
sudo systemctl enable pad

===> verifier l etat du service
sudo systemctl status pad








