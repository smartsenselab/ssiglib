#!/bin/bash

SSIG_DIR=`pwd`
BUILD_DIR=$SSIG_DIR/build

function lint()
{
  FILES_LINT=`( find . -name *.hpp -or -name *.cpp | grep "^./modules/" )`
  cpplint --counting=detailed --filter=-runtime/references $FILES_LINT
}

# function build()
# {
#   mkdir $BUILD_DIR && cd $BUILD_DIR
#   cmake -DBUILD_TESTS=OFF $SSF_DIR
#   make
# }
#
# function test()
# {
#   mkdir $BUILD_DIR && cd $BUILD_DIR
#   cmake -DBUILD_TESTS=ON $SSF_DIR
#   make
#   make test  ARGS="--output-on-failure"
# }
#
# function coverage()
# {
#   mkdir $BUILD_DIR && cd $BUILD_DIR
#   cmake -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON $SSF_DIR
#   make
#   make test ARGS="--output-on-failure"
# }

case $TASK in
  lint ) lint;;
  # test ) test;;
  # coverage ) coverage;;
esac
