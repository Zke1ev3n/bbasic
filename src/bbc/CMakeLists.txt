cmake_minimum_required(VERSION 3.9)
project(bbc)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-static-libstdc++")
add_executable(bbc
        main.cc
        token.cc
        lexer.cc
        parser.cc
        codegen.cc
        assembler.cc
        ast_dumper.cc
        identfinder.cc
        stringident.cc
        variable_set.cc
        utils.cc)
