cmake_minimum_required(VERSION 3.16)

project(sieve VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sieve src/sieve.cc)