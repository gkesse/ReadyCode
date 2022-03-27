#================================================
# configurer_serveur_systemd
#================================================
#
echo "=====>"
cat /etc/systemd/system/pad.service
#
echo "=====>"
cat << _EOF_ > /etc/systemd/system/pad.service
[Unit]
Description=pad service
After=network.target
StartLimitIntervalSec=0

[Service]
Type=simple
Restart=always
RestartSec=1
User=gkesse
ExecStart=/home/gkesse/Programs/ReadyCode/app/cpp/unix/code/src/data/server/server test socket/server/start

[Install]
WantedBy=multi-user.target
_EOF_
#
echo "=====>"
cat /etc/systemd/system/pad.service
#
echo "=====>"
sudo systemctl edit pad
#
echo "=====>"
sudo systemctl restart pad
#
echo "=====>"
sudo systemctl enable pad
#
echo "=====>"
systemctl daemon-reload
#
echo "=====>"
sudo systemctl status pad
#
