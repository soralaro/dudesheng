cmake_minimum_required(VERSION 3.10)
project(dudesheng)

set(CMAKE_CXX_STANDARD 11)

add_executable(dudesheng main.cpp)

target_link_libraries(dudesheng
        "-Wl,-Bdynamic"
        -lopencv_core
        -lopencv_imgproc
        -lopencv_imgcodecs
        )