cmake_minimum_required(VERSION 3.16)

project(ParachuteEncoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCES
    src/main.cpp
    src/ParachuteModel.cpp
    src/ParachuteView.cpp
    src/ParachuteController.cpp
    src/parachute.ui
)

set(HEADERS
    include/ParachuteModel.h
    include/ParachuteView.h
    include/ParachuteController.h
)

qt5_add_resources(MY_QRC_SOURCES resources.qrc)

add_executable(ParachuteEncoder
    ${SOURCES}
    ${HEADERS}
    ${MY_QRC_SOURCES}
)

target_link_libraries(ParachuteEncoder Qt5::Widgets)
