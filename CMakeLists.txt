cmake_minimum_required(VERSION 3.20)
project(hashing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WIN32_EXECUTABLE OFF)

include_directories(${PROJECT_SOURCE_DIR}/includes)
include_directories(${PROJECT_SOURCE_DIR}/include)


link_directories(${PROJECT_SOURCE_DIR})

add_executable(main_exec main.cpp studentreservationdef.cpp adminrep.cpp studentdata.cpp loginflow.cpp sessions.cpp)



target_link_libraries(main_exec bcrypt)


