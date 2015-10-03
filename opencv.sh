#!/bin/bash

sudo apt-get install -qq cmake
sudo apt-get install -qq libboost-filesystem1.54-dev libboost-log1.54-dev libboost-date-time1.54-dev libboost-thread1.54-dev
sudo apt-get install build-essential
sudo apt-get install git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
sudo apt-get install -qq gcc-4.8 g++-4.8
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 90
sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-4.8 90 

mkdir /home/travis/build/ssig/opencv/
cd /home/travis/build/ssig/opencv/
git clone https://github.com/Itseez/opencv.git

mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_OPENGL=ON ..

make # -j8 runs 8 jobs in parallel.
         # Change 8 to number of hardware threads available.
sudo make install

sudo sh -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'

sudo ldconfig
echo "OpenCV installed."

cd /home/travis/build/ssig/ssf/