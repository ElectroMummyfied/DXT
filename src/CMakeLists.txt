cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

project(COFG
  VERSION 1.0.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(CMakePrintHelpers)

find_package(PNG REQUIRED)
find_path(PNGPP_INCLUDE_DIRS "png++/color.hpp")

add_executable(COFG
  main.cxx
  dexter_sparse_vector.hxx dexter_sparse_vector.txx)

target_link_libraries(COFG PRIVATE ${PNG_LIBRARIES})
target_include_directories(COFG PRIVATE ${PNGPP_INCLUDE_DIRS})