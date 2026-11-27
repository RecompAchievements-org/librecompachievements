add_executable(rca_example_minimal minimal/main.c)
target_link_libraries(rca_example_minimal PRIVATE rca::rca)
rca_set_warnings(rca_example_minimal)
