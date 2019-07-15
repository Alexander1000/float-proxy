cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(float-proxy)

set(FLOAT_PROXY_SOURCES
    src/main.cpp
)

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${FLOAT_PROXY_SOURCES}
)
