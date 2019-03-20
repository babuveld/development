#!/usr/bin/env bash
#---------------------------------
#
# Build the infra libraries and run the
# test program
#
#----------------------------------

##########################################################
# Cleanup the existing build folder and create a new one #
##########################################################
rm -rf build
mkdir build
cd build

#######################
# Compile the targets #
# #####################
cmake ../
make

########################
# Run the test program #
########################
# ./test_main