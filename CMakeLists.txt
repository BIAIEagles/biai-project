cmake_minimum_required(VERSION 3.10)
# set the project name
project(SOM-image-compression VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
# add the executable
add_executable(SOM-image-compressor 
${CMAKE_SOURCE_DIR}/main.cpp
${CMAKE_SOURCE_DIR}/src/Pixel.cpp
)

target_include_directories(SOM-image-compressor PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
 )
target_link_libraries( SOM-image-compressor ${OpenCV_LIBS} )