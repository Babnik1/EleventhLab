set( CLIENT_SOURCES
    main.cpp
)

add_executable( join_client ${CLIENT_SOURCES} )

target_include_directories( join_client PRIVATE
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries( join_client PRIVATE
    Boost::system
)

set_target_properties( join_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)