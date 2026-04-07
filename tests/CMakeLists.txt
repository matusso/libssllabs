add_executable(ssllabs-tests ssllabs_tests.cpp)

target_include_directories(ssllabs-tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(ssllabs-tests PRIVATE ssllabs::static)

add_test(NAME ssllabs-tests COMMAND ssllabs-tests)
