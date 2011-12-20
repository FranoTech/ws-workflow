#!/bin/bash
dir=$1
a=`du -c $dir | grep total | cut -f 1`
b=$((a+512))
#echo "directory size: $a"
#echo "new block size: $b"
#echo "current directory: $dir"
sudo mount -t tmpfs -o size=$bM,mode=0777 tmpfs /home/lluu/dir

for i in `ls $dir`;
do
    sudo cp -r $dir/$i  /home/lluu/dir
done
