# Generated from uic.pro.

#####################################################################
## uic Tool:
#####################################################################

qt_add_tool(uic
    TARGET_DESCRIPTION "Qt User Interface Compiler"
    TOOLS_TARGET Widgets # special case
    SOURCES
        cpp/cppwritedeclaration.cpp cpp/cppwritedeclaration.h
        cpp/cppwriteincludes.cpp cpp/cppwriteincludes.h
        cpp/cppwriteinitialization.cpp cpp/cppwriteinitialization.h
        customwidgetsinfo.cpp customwidgetsinfo.h
        databaseinfo.cpp databaseinfo.h
        driver.cpp driver.h
        main.cpp
        option.h
        python/pythonwritedeclaration.cpp python/pythonwritedeclaration.h
        python/pythonwriteimports.cpp python/pythonwriteimports.h
        shared/language.cpp shared/language.h
        treewalker.cpp treewalker.h
        ui4.cpp ui4.h
        uic.cpp uic.h
        utils.h
        validator.cpp validator.h
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_FOREACH
        QT_UIC
    INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}
        # ${PROJECT_BINARY_DIR}/src/tools/uic # special case remove
        cpp
        python
        shared
    #PUBLIC_LIBRARIES # special case remove
        #Qt::Gui # special case remove
)

#### Keys ignored in scope 1:.:.:uic.pro:<TRUE>:
# QMAKE_TARGET_DESCRIPTION = "Qt User Interface Compiler"
# _OPTION = "host_build"

## Scopes:
#####################################################################
