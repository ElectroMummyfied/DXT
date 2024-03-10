cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

project(math
  LANGUAGES C CXX  )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(SDL2 CONFIG REQUIRED)
# find_package(SDL2_image CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

add_executable(cli src/main.cxx)
target_link_libraries(cli
  PRIVATE
    Eigen3::Eigen  )
    # SDL2::SDL2
    # SDL2::SDL2main
    # SDL2_image::SDL2_image  )