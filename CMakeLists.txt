cmake_minimum_required(VERSION 3.16)

project(taskify_desktop_qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(external/)

get_property(TASKIFY_EXECUTABLE_PATH GLOBAL PROPERTY TASKIFY_EXECUTABLE_PATH)
add_definitions(-DTASKIFY_EXECUTABLE="${TASKIFY_EXECUTABLE_PATH}")

qt_add_resources(RESOURCES qml.qrc)

qt_add_executable(apptaskify_desktop_qt
    main.cpp
    ${RESOURCES}
)

add_dependencies(apptaskify_desktop_qt taskify)

qt_add_qml_module(apptaskify_desktop_qt
    URI taskify_desktop_qt
    VERSION 1.0
    QML_FILES
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptaskify_desktop_qt PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptaskify_desktop_qt
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptaskify_desktop_qt
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apptaskify_desktop_qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
