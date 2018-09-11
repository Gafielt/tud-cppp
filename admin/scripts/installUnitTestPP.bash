#!/bin/bash

# This script installs UnitTest++ according to the instructions in 
# http://codelite.org/LiteEditor/UnitTestPP
#
# Author: Roland Kluge
# Date: 2018-09-11
#
apt install --yes --force-yes cmake
git clone https://github.com/unittest-cpp/unittest-cpp.git
cd unittest-cpp
mkdir build-release
cd build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
sudo make install