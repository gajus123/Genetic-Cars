#!/bin/bash

#Instalacja gcc
echo "Instalacja GCC"
sudo apt-get -y install gcc

#Instalacja Scons
echo "Instalacja Scons"
sudo apt-get -y install scons

#Instalacja boost
echo "Instalacja Boost-test"
sudo apt-get -y install libboost-test-dev

#Instalacja pkg-config
echo "Instalacja pkg-config"
sudo apt-get -y install pkg-config

#Pobiernie Box2D
echo "Pobieranie Box2D"
if [ ! -n "$(ls -A ./Box2D/)" ]
then
	sudo wget https://github.com/erincatto/Box2D/archive/master.zip
	unzip master.zip -d master
	mv master/Box2D-master/Box2D/Box2D ./
	rm -r master
	sudo rm master.zip
fi

#Pobieranie QT5.10.0
echo "Pobieranie instalatora QT"
sudo wget http://gensho.ftp.acc.umu.se/mirror/qt.io/qtproject/archive/online_installers/3.0/qt-unified-linux-x64-3.0.2-online.run
sudo chmod 755 qt-unified-linux-x64-3.0.2-online.run
./qt-unified-linux-x64-3.0.2-online.run