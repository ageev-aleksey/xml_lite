file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/lib/*.cpp)

add_library(xml-lite STATIC ${SRC})
target_include_directories(xml-lite  PUBLIC ${INCLUDE_DIR})
add_library(AAV::XML_LIB ALIAS xml-lite)

add_executable(app main.cpp)
target_link_libraries(app xml-lite stdc++fs)

install(TARGETS xml-lite app
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR})

