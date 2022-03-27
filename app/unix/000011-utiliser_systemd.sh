#================================================
# utiliser_systemd
#================================================

# ressources
https://medium.com/@benmorel/creating-a-linux-service-with-systemd-611b5c8b91d6
https://serverfault.com/questions/413397/how-to-set-environment-variable-in-systemd-service

# configurer un service
===> ouvrir le service
nano /etc/systemd/system/pad.service

===> configurer le service
[Unit]
Description=pad service
After=network.target
StartLimitIntervalSec=0

[Service]
EnvironmentFile=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/systemd/server.conf
Type=simple
Restart=always
RestartSec=1
User=gkesse
ExecStart=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/server/server test socket/server/start

[Install]
WantedBy=multi-user.target

===> demarrer le service
sudo systemctl start pad

===> demarrer le service au redemarrage
sudo systemctl enable pad

===> verifier l etat du service
sudo systemctl status pad

===> verifier l etat du service
sudo systemctl status pad

===> editer le service
sudo systemctl edit pad








