#!/bin/bash

echo "[*] wenetaunthreader (c) spv 2020, gplv2"
echo "[*] for your enjoyment, mussolini. "
printf "enter the bundle id of your jailbreak application. press enter for the default. (unc0ver) "

read bundleId

if [ $bundleId == "" ]
then
bundleId = "science.xnu.undecimus"
fi

echo "[*] got it. preparing ;)"
apt-get update
apt-get install -y python3 git
rm -rf /unthreader/
mkdir -p /unthreader/
git clone https://github.com/w212security/wenetaunthreader.git /unthreader/
mkdir -p /unthreader/patches/

echo $bundleId > /unthreader/bundleId.txt
python3 /unthreader/bin/cbp.py "$bundleId"
printf "would you like to copy launch daemons? (y/n) "
read launchDaemons
if [ $launchDaemons == "y" ]
then
cp -R /unthreader/daemons/* /
fi
cp -R /unthreader/bins/* /

echo "[*] theoretically done"
