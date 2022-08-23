cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

project(math
  LANGUAGES C CXX  )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
endif ()

add_executable(out
  src/vector.fxx
  src/vector.hxx
  src/vector.txx
  src/vector.cxx
  src/main.cxx
  )
target_include_directories(out
  PUBLIC
    ${CMAKE_SOURCE_DIR}/../boost/libs/preprocessor/include  )