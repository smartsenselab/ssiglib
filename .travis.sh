#!/bin/bash

SSIG_DIR=`pwd`
BUILD_DIR=$SSIG_DIR/build

function lint()
{
  FILES_LINT=`( find . -name *.hpp -or -name *.cpp | grep "^./modules/" )`
  cpplint --counting=detailed --filter=-runtime/references,-build/header_guard,-build/include_order $FILES_LINT
}

function test-gcc()
{
  mkdir opencv
  cd opencv
  wget https://github.com/Itseez/opencv/archive/3.1.0.zip
  unzip -qq 3.1.0.zip
  cd opencv-3.1.0
  mkdir build
  cd build
  cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=OFF -D WITH_FFMPEG=ON -D WITH_V4L=OFF -D WITH_OPENMP=ON -D BUILD_opencv_apps=OFF -D BUILD_DOCS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D BUILD_WITH_DEBUG_INFO=OFF -D BUILD_ANDROID_SERVICE=OFF ..
  make -j2
  sudo make install
  sudo /bin/bash -c 'echo "/usr/local/lib" > /etc/ld.so.conf.d/opencv.conf'
  sudo ldconfig
  cd ../../..
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON $SSIG_DIR
  make
  make test  ARGS="--output-on-failure"
}

case $TASK in
  lint ) lint;;
  test-gcc ) test-gcc;;
esac
