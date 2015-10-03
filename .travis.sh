#!/bin/bash

SSF_DIR=`pwd`
BUILD_DIR=$SSF_DIR/build

function build()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=OFF $SSF_DIR
  make
}

function test()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON $SSF_DIR
  make
  make test  ARGS="--output-on-failure"
}

function coverage()
{
  mkdir $BUILD_DIR && cd $BUILD_DIR
  cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON $SSF_DIR
  make
  make test ARGS="--output-on-failure"
}

case $TASK in
  build ) build;;
  test ) test;;
  coverage ) coverage;;
esac
