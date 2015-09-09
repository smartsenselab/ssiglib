#!/bin/bash

mkdir /home/travis/build/rbkloss/opencv/
cd /home/travis/build/rbkloss/opencv/
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

cd /home/travis/build/rbkloss/ssf/