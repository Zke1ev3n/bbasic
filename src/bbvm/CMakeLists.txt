cmake_minimum_required(VERSION 3.9)
project(bbvm)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(bbvm
        main.cc
        bbvm.cc
        renderer.cc
        inport.cc
        input_iml.cc
        outport.cc
        screen.cc
        storage.cc
        string_manager.cc
        utils.cc
        sdl.cc)

target_link_libraries(
        bbvm
        -lSDL2
        -lSDL2_ttf
        -liconv
)
