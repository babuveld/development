#*********************************** SETUP ***********************************

cmake_minimum_required (VERSION 2.8)

project (infra)

set(CMAKE_MACOSX_RPATH 1)

###########################
# Use c++11 compilation   #
###########################
set(CMAKE_CXX_STANDARD 11)

################
# Locate GTest #
################
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#################################
# Search path for include files #
#################################
include_directories (
    include
    src
    )

##############################################
# Build directory location for the link path #
##############################################
link_directories(${CMAKE_CURRENT_BINARY_DIR})

#********************************* SOURCES *************************************

#############################
# Infra Library Source code #
#############################
set (SRC_INFRA
    src/unordered_hmap.cpp
    )

####################
# Test Source code #
####################
set (SRC_TEST
     test/src/test_main.cpp
     test/src/test_unordered_hmap.cpp
    )

#*********************************** TARGETS ***********************************

######################
# Create the library #
######################
add_library (infra SHARED ${SRC_INFRA})

################
# Test Program #
################
add_executable (test_main ${SRC_TEST})
target_link_libraries(test_main ${GTEST_LIBRARIES} infra pthread)

#********************************************************************************