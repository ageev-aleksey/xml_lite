cmake_minimum_required(VERSION 3.10)

project(xml_demon)

option(TEST_COMPILE "to compile tests?" ON)
option(BUILD_DOC "Build documentation" ON)


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


if(BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_LIST_DIR}/doc/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_LIST_DIR}/Doxyfile)

        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message(STATUS "Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/doc
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM )
    else (DOXYGEN_FOUND)
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif(BUILD_DOC)