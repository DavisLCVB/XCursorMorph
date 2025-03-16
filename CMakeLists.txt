cmake_minimum_required(VERSION 3.20)
project(XCursorMorph LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

find_package(Qt6 COMPONENTS Core Widgets Gui REQUIRED)

file(GLOB_RECURSE LIB_SOURCES "source/*.cpp" "source/*.hpp" "source/*.ui" "assets/assets.qrc")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/source/main.cpp")
set(EXE_SOURCES "source/main.cpp")
set(LIB_NAME "${PROJECT_NAME}-lib")
set(EXE_NAME "${PROJECT_NAME}")
configure_file("source/meta/meta.conf.hpp" "${CMAKE_BINARY_DIR}/metadata/meta.hpp")

add_library(${LIB_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${LIB_NAME} PUBLIC "source" "${CMAKE_BINARY_DIR}")
target_link_libraries(${LIB_NAME} PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

add_executable(${EXE_NAME} ${EXE_SOURCES})
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME} Qt6::Core Qt6::Widgets Qt6::Gui)
target_include_directories(${EXE_NAME} PRIVATE "source" "${CMAKE_BINARY_DIR}")
add_subdirectory("tests")
