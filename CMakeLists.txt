cmake_minimum_required(VERSION 3.21)

project(librecompachievements
    VERSION 1.0.0
    DESCRIPTION "C/C++ client SDK for RecompAchievements"
    HOMEPAGE_URL "https://recompachievements.org/"
    LANGUAGES C CXX)

# Pre-release label of the version being built; empty for a final release.
set(RCA_VERSION_PRERELEASE "alpha.1")
if(RCA_VERSION_PRERELEASE)
    set(RCA_VERSION_STRING "${PROJECT_VERSION}-${RCA_VERSION_PRERELEASE}")
else()
    set(RCA_VERSION_STRING "${PROJECT_VERSION}")
endif()

option(RCA_BUILD_TESTS "Build the librecompachievements tests" ${PROJECT_IS_TOP_LEVEL})
option(RCA_BUILD_EXAMPLES "Build the librecompachievements examples" ${PROJECT_IS_TOP_LEVEL})
option(RCA_INSTALL "Generate the librecompachievements install target" ${PROJECT_IS_TOP_LEVEL})
option(RCA_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif()

include(GNUInstallDirs)
include(GenerateExportHeader)
include("${PROJECT_SOURCE_DIR}/cmake/CompilerWarnings.cmake")

set(RCA_GENERATED_INCLUDE_DIR "${PROJECT_BINARY_DIR}/include")
configure_file(cmake/version.h.in "${RCA_GENERATED_INCLUDE_DIR}/rca/version.h" @ONLY)

add_library(rca
    src/version.cpp)
add_library(rca::rca ALIAS rca)

target_compile_features(rca PUBLIC c_std_99 PRIVATE cxx_std_17)
target_include_directories(rca
    PUBLIC
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${RCA_GENERATED_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    PRIVATE
        "${PROJECT_SOURCE_DIR}/src")
set_target_properties(rca PROPERTIES
    OUTPUT_NAME recompachievements
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    EXPORT_NAME rca)
rca_set_warnings(rca)

generate_export_header(rca
    BASE_NAME RCA
    EXPORT_MACRO_NAME RCA_API
    EXPORT_FILE_NAME "${RCA_GENERATED_INCLUDE_DIR}/rca/export.h")
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(rca PUBLIC RCA_STATIC_DEFINE)
endif()

if(RCA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(RCA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(RCA_INSTALL)
    include(CMakePackageConfigHelpers)
    set(RCA_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/librecompachievements")

    install(TARGETS rca
        EXPORT librecompachievementsTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/rca "${RCA_GENERATED_INCLUDE_DIR}/rca"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(EXPORT librecompachievementsTargets
        NAMESPACE rca::
        DESTINATION "${RCA_CMAKE_INSTALL_DIR}")

    configure_package_config_file(cmake/librecompachievementsConfig.cmake.in
        "${PROJECT_BINARY_DIR}/librecompachievementsConfig.cmake"
        INSTALL_DESTINATION "${RCA_CMAKE_INSTALL_DIR}")
    write_basic_package_version_file("${PROJECT_BINARY_DIR}/librecompachievementsConfigVersion.cmake"
        COMPATIBILITY SameMajorVersion)
    install(FILES
        "${PROJECT_BINARY_DIR}/librecompachievementsConfig.cmake"
        "${PROJECT_BINARY_DIR}/librecompachievementsConfigVersion.cmake"
        DESTINATION "${RCA_CMAKE_INSTALL_DIR}")
    install(FILES LICENSE-MIT LICENSE-APACHE
        DESTINATION "${CMAKE_INSTALL_DOCDIR}")
endif()
