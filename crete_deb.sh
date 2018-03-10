#!/bin/bash
export TERM=xterm
#https://habrahabr.ru/post/78094/
#Programm
cp ./MxBlog/dist/ReleaseX64/GNU-Linux/mxblog ./deb/usr/local/mxblog/mxblog
chmod 755 ./deb/usr/local/mxblog/mxblog
#chgrp www ./deb/usr/local/mxblog/mxblog
#Link Programm
rm ./deb/usr/bin/mxblog
ln -s /usr/local/mxblog/mxblog ./deb/usr/bin/mxblog
#MD5
md5deep -l -o f -r ./deb/usr > ./deb/DEBIAN/md5sums
#Create DEB pakege
fakeroot dpkg-deb --build deb
#Rename and move
mv ./deb.deb ./PublicBuild/mxblog64.deb
