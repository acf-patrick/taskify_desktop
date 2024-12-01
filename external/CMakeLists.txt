cmake_minimum_required(VERSION 3.16)

# Define a custom target to build the Rust project executable
add_custom_target(
    taskify ALL
    COMMAND cargo build --release --package cli
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/taskify
    COMMENT "Building taskify main executable"
)

set(TASKIFY_EXECUTABLE_NAME taskify)

if (WIN32)
    set(TASKIFY_EXECUTABLE_NAME ${TASKIFY_EXECUTABLE_NAME}.exe)
endif()

# Specify the output location of the Rust executable
set(TASKIFY_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/taskify/target/release/${TASKIFY_EXECUTABLE_NAME})

set_property(
    GLOBAL
    PROPERTY TASKIFY_EXECUTABLE_PATH ${TASKIFY_EXECUTABLE})

set_property(
    GLOBAL
    PROPERTY TASKIFY_EXECUTABLE_NAME ${TASKIFY_EXECUTABLE_NAME})

# Make the path available to the main project
add_custom_target(taskify_exec DEPENDS taskify)
