#!/bin/bash

ls ~ -alh | grep .bashrc

echo "export HELLO=HOSTNAME" >> ~/.bashrc

echo "LOCAL=$(whoami)" >> ~/.bashrc

terminator
