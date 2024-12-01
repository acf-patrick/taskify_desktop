cmake_minimum_required(VERSION 3.16)

# Define a custom target to build the Rust project executable
add_custom_target(
    taskify ALL
    COMMAND cargo build --release
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/taskify
    COMMENT "Building taskify main executable"
)

# Specify the output location of the Rust executable
set(TASKIFY_EXECUTBALE ${CMAKE_CURRENT_SOURCE_DIR}/taskify/target/release/taskify)

if (WIN32)
    set(TASKIFY_EXECUTBALE ${TASKIFY_EXECUTABLE}.exe)
endif()

set_property(GLOBAL PROPERTY TASKIFY_EXECUTABLE_PATH ${TASKIFY_EXECUTBALE})

# Make the path available to the main project
add_custom_target(rust_exec DEPENDS taskify)
