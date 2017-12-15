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

#Pobieranie QT5-tool
echo "Pobieranie Scons QT5-tool"
if [ ! -n "$(ls -A ./site_scons/site_tools/qt5)" ]
then
	sudo wget https://bitbucket.org/dirkbaechle/scons_qt5/get/9caa36eb469d.zip
	unzip 9caa36eb469d.zip -d 9caa36eb469d
	mkdir -p ./site_scons/site_tools/qt5/
	mv ./9caa36eb469d/dirkbaechle-scons_qt5-9caa36eb469d/* ./site_scons/site_tools/qt5/
	rm -r 9caa36eb469d
	sudo rm 9caa36eb469d.zip
	rm -r ./site_scons/site_tools/qt5/test
fi

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

