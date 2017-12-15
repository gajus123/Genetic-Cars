#!/bin/bash

#Instalacja gcc
echo "Instalacja GCC"
sudo apt-get -y install gcc

#Instalacja QT5
echo "Instalacja QT5"
sudo apt-get -y install qtbase5-dev

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

