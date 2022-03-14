#================================================
# installation_dbeaver_ubuntu
#================================================

sudo -i
apt update
apt upgrade -y
cd /opt
wget https://dbeaver.io/files/22.0.0/dbeaver-ce_22.0.0_amd64.deb

sudo apt update
sudo apt upgrade -y
sudo apt install default-jdk -y
sudo apt install snapd -y
sudo reboot

sudo snap install core
sudo snap install --edge dbeaver-ce
