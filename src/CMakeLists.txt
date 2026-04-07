set(SSLLABS_SOURCE_FILES
    analyze.cpp
    endpoint.cpp
    getInfo.cpp
    parsers.cpp
    ssllabs.cpp
)

add_library(ssllabs-shared SHARED ${SSLLABS_SOURCE_FILES})
add_library(ssllabs-static STATIC ${SSLLABS_SOURCE_FILES})

add_library(ssllabs::shared ALIAS ssllabs-shared)
add_library(ssllabs::static ALIAS ssllabs-static)

set(SSLLABS_STATIC_OUTPUT_NAME ssllabs)
if(WIN32)
    set(SSLLABS_STATIC_OUTPUT_NAME ssllabs-static)
endif()

set_target_properties(ssllabs-shared PROPERTIES
    OUTPUT_NAME ssllabs
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

set_target_properties(ssllabs-static PROPERTIES
    OUTPUT_NAME ${SSLLABS_STATIC_OUTPUT_NAME}
)

foreach(target IN ITEMS ssllabs-shared ssllabs-static)
    target_compile_features(${target} PUBLIC cxx_std_17)
    target_include_directories(${target}
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include/rapidjson/include
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
    target_link_libraries(${target} PUBLIC CURL::libcurl)
endforeach()

install(TARGETS ssllabs-shared ssllabs-static
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/ssllabs"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/ssllabs"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
