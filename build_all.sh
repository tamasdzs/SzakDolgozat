#!/bin/bash

echo "***************************************************************************************************"
echo "Welcome to EcgCompression with Hermite functions by Tamas Dozsa. Preparing to set up your experience..."
echo "***************************************************************************************************"

ROOT_DIR=`pwd`

#Grant rights
echo "setting rights..."
chmod -R 777 ./www
if [ $? -ne 0 ]
then
	echo "***************************************************************************************************"
	echo "Setting rights for www folders failed. Make sure you run this script as root. (sudo ./build_all.sh)"
	echo "Exiting..."
	echo "***************************************************************************************************"
	return -1
fi
echo "setting rights: [OK]"

#Build cpp
echo "building executable from source..."
cd ./src
make -f szdMakeFile
if [ $? -ne 0 ]
then
	echo "***************************************************************************************************"
	echo "C++ build failed. Make sure you have all of the prerequisites installed (wfdb, eigen, curl, etc...)"
	echo "Exiting..."
	echo "***************************************************************************************************"
	return -1
fi
echo "building executable from source: [OK]"

#Create link to executable
echo "creating symbolic link to main"
cd $ROOT_DIR
cd ./www/szd/cpp
ln -sf ../../../src/main
if [ $? -ne 0 ]
then
	echo "***************************************************************************************************"
	echo "Creating symbolic link to executable failed. Make sure you run this script as root. (sudo ./build_all.sh)"
	echo "Exiting..."
	echo "***************************************************************************************************"
	return -1
fi
echo "creating symbolic link to main: [OK]"

echo "***************************************************************************************************"
echo "Build finished with status OK"
echo "Exiting..."
echo "***************************************************************************************************"
return 0
