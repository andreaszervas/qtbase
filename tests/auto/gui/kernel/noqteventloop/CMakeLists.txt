# Generated from noqteventloop.pro.

#####################################################################
## tst_noqteventloop Test:
#####################################################################

add_qt_test(tst_noqteventloop
    SOURCES
        tst_noqteventloop.cpp
    PUBLIC_LIBRARIES
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::Network
)

## Scopes:
#####################################################################

extend_target(tst_noqteventloop CONDITION QT_FEATURE_dynamicgl AND WIN32 AND NOT WINRT
    PUBLIC_LIBRARIES
        user32
)
