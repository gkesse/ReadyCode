sudo nano /etc/apt/sources.list

deb [arch=arm64] http://ports.ubuntu.com/ focal main multiverse universe
deb [arch=arm64] http://ports.ubuntu.com/ focal-security main multiverse universe
deb [arch=arm64] http://ports.ubuntu.com/ focal-backports main multiverse universe
deb [arch=arm64] http://ports.ubuntu.com/ focal-updates main multiverse universe

sudo dpkg --print-foreign-architectures
sudo dpkg --add-architecture arm64
sudo dpkg --print-foreign-architectures

sudo apt update
sudo apt upgrade

