file(GLOB_RECURSE SRC_TEST ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
set(INCLUDE_TEST_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(tests ${SRC_TEST})
target_include_directories(tests PUBLIC ${INCLUDE_TEST_DIR})
target_link_libraries(tests AAV::XML_LIB)

install(TARGETS tests
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR})