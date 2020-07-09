file(GLOB_RECURSE SRC_TEST ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
set(INCLUDE_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(test ${SRC_TEST})
target_include_directories(test PUBLIC ${INCLUDE_TEST_DIR})
target_link_libraries(test AAV::XML_LIB)

install(TARGETS test
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR})