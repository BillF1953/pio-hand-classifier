

cmake_minimum_required(VERSION 3.8)
project(HandClassifier)
set(CMAKE_CXX_STANDARD 11)
if(WIN32)
    include_directories("..\\fast-cpp-csv-parser")
    set(SOURCE_FILES src\\main.cpp src\\HandClassifier.cpp src\\HandClassifier.h tst\\catch.hpp tst\\Hand_Classifier_Tests.cpp)
endif(WIN32)

if(UNIX)
    include_directories("../fast-cpp-csv-parser")
    set(SOURCE_FILES src/main.cpp src/HandClassifier.cpp src/HandClassifier.h tst/catch.hpp tst/Hand_Classifier_Tests.cpp)
    set (CMAKE_CXX_FLAGS "-fPIC")
endif(UNIX)



add_executable(HandClassifier ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(HandClassifier pthread)