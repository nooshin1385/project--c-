cmake_minimum_required(VERSION 4.1)
project(hashing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/includes)


include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} source.cpp)


target_link_libraries(${PROJECT_NAME} bcrypt)