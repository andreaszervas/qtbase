# Generated from mimetypebrowser.pro.

cmake_minimum_required(VERSION 3.14)
project(mimetypebrowser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(INSTALL_EXAMPLEDIR "examples/corelib/mimetypes/mimetypebrowser")

find_package(Qt6 COMPONENTS Core)
find_package(Qt6 COMPONENTS Gui)
find_package(Qt6 COMPONENTS Widgets)

add_executable(mimetypebrowser
    main.cpp
    mainwindow.cpp mainwindow.h
    mimetypemodel.cpp mimetypemodel.h
)
target_link_libraries(mimetypebrowser PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Widgets
)

install(TARGETS mimetypebrowser
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
