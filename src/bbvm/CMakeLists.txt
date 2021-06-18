cmake_minimum_required(VERSION 3.9)
project(bbvm)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(bbvm
        main.cc
        bbvm.cc
        Cpu.cpp
        Gpu.cpp
        InPort.cpp
        Input.cpp
        OutPort.cpp
        Screen.cpp
        Storage.cpp
        String.cpp
        utils.cpp
        )

target_link_libraries(
        bbvm
        -lSDL2
        -lSDL2_ttf
        -liconv
)
