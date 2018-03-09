#!/bin/bash

echo "Installing default packages..."
sudo apt-get update
sudo apt-get install build-essential git uuid-dev libboost-all-dev libssl-dev cmake

echo "Cloning HTTP Server..."
git clone https://github.com/lpereira/lwan
cd lwan
sudo mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make


echo "Cloning COSSB"
git clone https://github.com/nsynapse/cossb.git
cd cossb
make timbo
sudo make install