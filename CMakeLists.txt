cmake_minimum_required(VERSION 3.12)

project(bulk)

set (CMAKE_CXX_STANDARD 17)

add_executable(bulk
    src/main.cpp
    src/cmd.cpp
    src/writers.cpp
    src/observer.h
    src/stdafx.h
)

target_include_directories(bulk
    PRIVATE "${CMAKE_BINARY_DIR}"
)

install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME "bulk")
set(CPACK_PACKAGE_CONTACT art.shestakov@icloud.com)
include(CPack)
