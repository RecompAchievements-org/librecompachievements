# Consumes an installed librecompachievements through find_package, the way a recomp would.
# CI installs the SDK to a prefix, then configures this project with CMAKE_PREFIX_PATH set to it.
cmake_minimum_required(VERSION 3.21)

project(rca_package_test LANGUAGES C CXX)

find_package(librecompachievements 1 REQUIRED)

add_executable(rca_package_test main.c)
target_link_libraries(rca_package_test PRIVATE rca::rca)
