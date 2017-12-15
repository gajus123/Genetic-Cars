#!/bin/bash

#Install gcc
sudo apt-get -y install gcc

#Install Make
sudo apt-get -y install make

#Install QT5
sudo apt-get -y install qtbase5-dev
#sudo apt-get -y install qt5-default

#sudo apt-get update
#sudo apt-get install build-essential checkinstall
#sudo apt-get install libreadline-gplv2-dev libncursesw5-dev libssl-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev
#Install Python 2.7.14
#if ! command -v python >/dev/null 2>&1;
#then
#	cd /usr/src
#	sudo wget https://www.python.org/ftp/python/2.7.14/Python-2.7.14.tgz
#	sudo tar xzf Python-2.7.14.tgz
#	cd Python-2.7.14
#	sudo ./configure
#	sudo make altinstall
#fi


#Install Scons
sudo apt-get -y install scons

#Install boost
sudo apt-get -y install libboost-test-dev

#Download QT5 tool
if [ ! -n "$(ls -A ~/.scons/)" ]
then
	echo "No QT5 tool"
	sudo wget https://bitbucket.org/dirkbaechle/scons_qt5/get/9caa36eb469d.zip
	unzip 9caa36eb469d.zip -d 9caa36eb469d
	mkdir -p ~/.scons/site_scons/site_tools/qt5/
	mv ./9caa36eb469d/dirkbaechle-scons_qt5-9caa36eb469d/* ~/.scons/site_scons/site_tools/qt5/
	rm -r 9caa36eb469d
	sudo rm 9caa36eb469d.zip
fi

#Install pkg-config
sudo apt-get -y install pkg-config

#Download Box2D
if [ ! -n "$(ls -A ./Box2D/)" ]
then
	sudo wget https://github.com/erincatto/Box2D/archive/master.zip
	unzip master.zip -d master
	mv master/Box2D-master/Box2D/Box2D ./
	rm -r master
	sudo rm master.zip
fi

