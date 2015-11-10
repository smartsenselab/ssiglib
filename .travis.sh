#!/bin/bash

SSIG_DIR=`pwd`
BUILD_DIR=$SSIG_DIR/build

function lint()
{
  FILES_LINT=`( find . -name *.hpp -or -name *.cpp | grep "^./modules/" )`
  cpplint --counting=detailed --filter=-runtime/references $FILES_LINT
}

function test-gcc()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON $SSIG_DIR
  make
  make test  ARGS="--output-on-failure"
}

function test-clang()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON $SSIG_DIR
  make
  make test  ARGS="--output-on-failure"
}

case $TASK in
  lint ) lint;;
  test-gcc ) test-gcc;;
  test-clang ) test-clang;;;;
esac
