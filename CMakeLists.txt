cmake_minimum_required(VERSION 3.16)

project(ParachuteEncoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/ParachuteModel.cpp
    src/ParachuteView.cpp
    src/ParachuteController.cpp
)

set(HEADERS
    include/ParachuteModel.h
    include/ParachuteView.h
    include/ParachuteController.h
)

add_executable(ParachuteEncoder ${SOURCES} ${HEADERS})

target_link_libraries(ParachuteEncoder Qt5::Widgets)
