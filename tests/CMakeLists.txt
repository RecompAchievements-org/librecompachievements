add_library(rca_doctest INTERFACE)
target_include_directories(rca_doctest SYSTEM INTERFACE "${PROJECT_SOURCE_DIR}/third_party")
# Includes the real standard headers instead of doctest's forward declarations of std types,
# which newer MSVC standard libraries reject when a test prints a std::string_view.
target_compile_definitions(rca_doctest INTERFACE DOCTEST_CONFIG_USE_STD_HEADERS)

add_executable(rca_tests
    main.cpp
    version_test.cpp)
target_link_libraries(rca_tests PRIVATE rca::rca rca_doctest)
target_compile_features(rca_tests PRIVATE cxx_std_17)
rca_set_warnings(rca_tests)
# Test code uses doctest macros, which clang-tidy reports on; the library itself is still checked.
set_target_properties(rca_tests PROPERTIES CXX_CLANG_TIDY "")
add_test(NAME rca_tests COMMAND rca_tests)

# Builds the public header as C, so C recomps can include it, and checks it against the library.
add_executable(rca_c_header_test c_header_test.c)
target_link_libraries(rca_c_header_test PRIVATE rca::rca)
rca_set_warnings(rca_c_header_test)
add_test(NAME rca_c_header_test COMMAND rca_c_header_test)

if(WIN32 AND BUILD_SHARED_LIBS)
    set_tests_properties(rca_tests rca_c_header_test PROPERTIES
        ENVIRONMENT_MODIFICATION "PATH=path_list_prepend:$<TARGET_FILE_DIR:rca>")
endif()
