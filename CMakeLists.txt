cmake_minimum_required( VERSION 3.12 )

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

project( join_server VERSION 1.0 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

find_package( Boost REQUIRED COMPONENTS program_options filesystem system )
find_package( nlohmann_json REQUIRED )

set( SOURCES 
        src/server/server.cpp
        src/server/session.cpp
        src/handler/handler.cpp
        src/dataManager/data_manager.cpp
        main.cpp 
)

add_executable( join_server ${SOURCES} )

add_subdirectory( client )

target_include_directories( join_server PRIVATE ${CMAKE_SOURCE_DIR} )

target_include_directories( join_server PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

set_target_properties( join_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} )


# Упаковка в пакет.

install( TARGETS join_server RUNTIME DESTINATION bin )

# Версия пакета берётся из git-тэга либо задаётся вручную
if ( NOT DEFINED PROJECT_VERSION_PATCH )
    set( PROJECT_VERSION_PATCH 0 )
endif()

set( CPACK_GENERATOR "DEB" )

set( CPACK_PACKAGE_NAME "join_server" )
set( CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}" )
set( CPACK_PACKAGE_CONTACT "inodoropavel@gmail.com" )

set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pasha" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system1.74.0, libboost-filesystem1.74.0, libboost-program-options1.74.0" )

include( CPack )