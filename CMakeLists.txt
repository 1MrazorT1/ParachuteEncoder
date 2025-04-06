cmake_minimum_required(VERSION 3.16)

project(ParachuteEncoder LANGUAGES CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# If not using a multi-config generator, default to Debug
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Include paths
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/ParachuteModel.cpp
    src/ParachuteView.cpp
    src/ParachuteController.cpp
    src/parachute.ui
)

# Header files
set(HEADERS
    include/ParachuteModel.h
    include/ParachuteView.h
    include/ParachuteController.h
)

# Resources (QRC)
qt5_add_resources(MY_QRC_SOURCES resources.qrc)

# Define the executable
add_executable(ParachuteEncoder
    ${SOURCES}
    ${HEADERS}
    ${MY_QRC_SOURCES}
)

# Link against Qt Widgets
target_link_libraries(ParachuteEncoder Qt5::Widgets)
