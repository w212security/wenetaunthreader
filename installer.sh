#!/bin/bash

echo "[*] THIS IS BROKEN! USE MASTER FOR NOW!"
exit -1
echo "[*] wenetaunthreader (c) spv 2020, gplv2"
echo "[*] for your enjoyment, mussolini. "
printf "enter the bundle id of your jailbreak application. type 'd' for the default. see notes.md for more info"

read bundleId

if [ $bundleId == "d" ]
then
	bundleId = "science.xnu.undecimus"
fi

echo "[*] got it. preparing ;)"
apt-get update
apt-get install -y python3 git
rm -rf /unthreader/
mkdir -p /unthreader/
if [ -e __IS_WEU_REPO ]
then
	echo "[*] using local files"
	cp -R ./* /unthreader/
else
	git clone https://github.com/w212security/wenetaunthreader.git /unthreader/
fi
mkdir -p /unthreader/patches/

echo $bundleId > /unthreader/bundleId.txt
python3 /unthreader/bin/cbp.py "$bundleId"
printf "would you like to copy launch daemons? (y/n) "
read launchDaemons
if [ $launchDaemons == "y" ]
then
	echo "[*] copying daemons"
	cp -R /unthreader/daemons/* /
fi
echo "[*] copying binaries"
cp -R /unthreader/bins/* /

echo "[*] cleaning up"
rm -rf /unthreader/bins /unthreader/*.md /unthreader/daemons/ /unthreader/installer.sh

echo "[*] theoretically done"
