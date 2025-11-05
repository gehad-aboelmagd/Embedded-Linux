#!/bin/bash

var=$(ls -a ~ | grep .bashrc)

if [ $var = "" ]; then 
	echo "file wasn't found"
else 
	echo "file already exists";
	echo "export HELLO=$HOSTNAME" >> ~/.bashrc;
	echo "LOCAL=$(whoami)" >> ~/.bashrc;
fi

terminator
