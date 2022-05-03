#!/bin/bash

apt-get update

# sudo apt-get install libx11-dev -y
# sudo apt-get install xorg-dev -y
# sudo apt-get install gnuplot -y

# sudo apt-get install libprotobuf-dev -y
# sudo apt-get install protobuf-compiler -y
# sudo apt-get install libboost-dev -y

# sudo apt-get install autoconf -y
# sudo apt-get install python-pip -y
# sudo apt-get install python-matplotlib -y

# sudo apt-get install build-essential -y


sudo apt-get install -y g++-4.9
sudo apt-get install -y protobuf-compiler
sudo apt-get install -y libprotobuf-dev
sudo apt-get install -y libgl1-mesa-dev
sudo apt-get install -y libglew-dev
sudo apt-get install -y libcairo2-dev
sudo apt-get install -y libpango1.0-dev
sudo apt-get install -y libgtkmm-3.0-dev
sudo apt-get install -y libboost-dev
sudo apt-get install -y libglu1-mesa-dev
sudo apt-get install -y python3-matplotlib
sudo apt-get install -y python3-numpy
sudo apt-get install -y autoconf

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.9 -y
sudo apt-get install g++-4.9 -y
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 99
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.9 99

sudo add-apt-repository -y 'deb http://ppa.launchpad.net/keithw/glfw3/ubuntu trusty main'
sudo apt-get update
sudo apt-get install -y --force-yes libglfw3-dev
