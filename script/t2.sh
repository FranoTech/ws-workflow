#!/bin/bash
dir=$1
a=`du -c $dir | grep total | cut -f 1`
b=$((a+50))
#echo "directory size: $a"
#echo "new block size: $b"
#echo "current directory: $dir"
sudo mount -t tmpfs -o size=$bM,mode=0777 tmpfs /var/www/cgi-bin/image

for i in `ls $dir`;
do
    sudo cp -r $dir/$i  /var/www/cgi-bin/image/
done
