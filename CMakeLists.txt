cmake_minimum_required(VERSION 3.16)

project(taskify_desktop_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.2)

add_subdirectory(external/)

get_property(TASKIFY_EXECUTABLE_NAME GLOBAL PROPERTY TASKIFY_EXECUTABLE_NAME)
get_property(TASKIFY_EXECUTABLE_PATH GLOBAL PROPERTY TASKIFY_EXECUTABLE_PATH)

add_definitions(-DTASKIFY_EXECUTABLE="${TASKIFY_EXECUTABLE_PATH}")
add_definitions(-DTASKIFY_EXECUTABLE_NAME="${TASKIFY_EXECUTABLE_NAME}")

qt_add_resources(RESOURCES qml.qrc)

qt_add_executable(taskify_desktop
    main.cpp
    ${RESOURCES}
)

add_dependencies(taskify_desktop taskify)

add_custom_command(
    TARGET taskify_desktop
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${TASKIFY_EXECUTABLE_PATH}
            $<TARGET_FILE_DIR:taskify_desktop>/${TASKIFY_EXECUTABLE_NAME}
    COMMENT "Copying Taskify executable to output directory"
)

qt_add_qml_module(taskify_desktop
    URI taskify_desktop_qt
    VERSION 1.0
    QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(taskify_desktop PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.taskify_desktop
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(taskify_desktop
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS taskify_desktop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# install taskify executable as part of the same process
install(
    FILES ${CMAKE_BINARY_DIR}/external/taskify/target/release/${TASKIFY_EXECUTABLE_NAME}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
)
