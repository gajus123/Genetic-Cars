#!/bin/bash

#Install gcc
echo "Install GCC"
sudo apt-get -y install gcc

#Install Make
echo "Install Make"
sudo apt-get -y install make

#Install QT5
echo "Install QT5"
sudo apt-get -y install qtbase5-dev

#Install Scons
echo "Install Scons"
sudo apt-get -y install scons

#Install boost
echo "Install Boost-test"
sudo apt-get -y install libboost-test-dev

#Download QT5 tool
echo "Download Scons QT5 tool"
if [ ! -n "$(ls -A ./site_scons/site_tools/qt5)" ]
then
	echo "No QT5 tool"
	sudo wget https://bitbucket.org/dirkbaechle/scons_qt5/get/9caa36eb469d.zip
	unzip 9caa36eb469d.zip -d 9caa36eb469d
	mkdir -p ./site_scons/site_tools/qt5/
	mv ./9caa36eb469d/dirkbaechle-scons_qt5-9caa36eb469d/* ./site_scons/site_tools/qt5/
	rm -r 9caa36eb469d
	sudo rm 9caa36eb469d.zip
	rm -r ./site_scons/site_tools/qt5/test
fi

#Install pkg-config
echo "Install pkg-config"
sudo apt-get -y install pkg-config

#Download Box2D
echo "Download Box2D"
if [ ! -n "$(ls -A ./Box2D/)" ]
then
	sudo wget https://github.com/erincatto/Box2D/archive/master.zip
	unzip master.zip -d master
	mv master/Box2D-master/Box2D/Box2D ./
	rm -r master
	sudo rm master.zip
fi

