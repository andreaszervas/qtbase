# Generated from qmutex.pro.

#####################################################################
## tst_qmutex Test:
#####################################################################

add_qt_test(tst_qmutex
    SOURCES
        tst_qmutex.cpp
)

## Scopes:
#####################################################################

extend_target(tst_qmutex CONDITION WIN32
    PUBLIC_LIBRARIES
        Qt::CorePrivate
)
