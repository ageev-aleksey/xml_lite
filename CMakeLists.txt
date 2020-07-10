cmake_minimum_required(VERSION 3.12)

project(xml_demon)

option(TEST_COMPILE "to compile tests?" ON)


set(INCLUDE_DIR          ${CMAKE_CURRENT_LIST_DIR}/include)
set(SRC_DIR              ${CMAKE_CURRENT_LIST_DIR}/src)
set(TEST_DIR             ${CMAKE_CURRENT_LIST_DIR}/test)
set(INSTALL_RUNTIME_DIR  ${CMAKE_CURRENT_LIST_DIR}/bin)
set(INSTALL_ARCHIVE_DIR  ${INSTALL_RUNTIME_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${SRC_DIR})

if(${TEST_COMPILE})
    message(STATUS "Will be compile tests")
    add_subdirectory(${TEST_DIR})
endif()
