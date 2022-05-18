#================================================
https://cppsecrets.com/users/36681111069711511910546971161041031049711497575664103109971051084699111109/Ubuntu-install-poco-C00-library-Linux.php
#================================================
sudo apt update
sudo apt upgrade
#================================================
sudo apt install build-essential
sudo apt install gdb
sudo apt install cmake
sudo apt install git
#================================================
sudo apt install openssl
sudo apt install libssl-dev
sudo apt install libiodbc2
sudo apt install libiodbc2-dev
sudo apt install libmysqlclient-dev
sudo apt install libpq-dev
sudo apt install libpoco-dev
#================================================
sudo -i
cd /opt
git clone -b master https://github.com/pocoproject/poco.git
cd poco
mkdir cmake-build
cd cmake-build
cmake ..
cmake --build . --config Release
cmake --build . --target install
#================================================
