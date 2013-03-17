#!/bin/bash
if mount | grep "on /home/lluu/thesis/result type" > /dev/null
then
		echo "old tmpfs unmounted"
		sudo umount /home/lluu/thesis/result
fi

echo "new tmpfs mounted"
sudo mount -t tmpfs -o size=256m tmpfs /home/lluu/thesis/result
cp /home/lluu/thesis/config.cfg /home/lluu/thesis/result/

