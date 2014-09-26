QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")
QT_VER_MAJ = $$member(QT_VERSION, 0)
QT_VER_MIN = $$member(QT_VERSION, 1)

lessThan(QT_VER_MAJ, 4) {
   lessThan(QT_VER_MIN, 5){
   error(psvlib requires Qt 4.5 or newer but Qt $$[QT_VERSION] was detected.)
}
}else{
lessThan(QT_VER_MAJ, 5) {
DEFINES += VERSION_4
message(当前版本:VERSION_4)
}else{
DEFINES += VERSION_5
QT += widgets
message(当前版本:VERSION_5)
}
}
message(当前版本:$$[QT_VERSION])
#message($$sprintf(%1,$$member(QT_VERSION, 1)))

#注释下行，编译lib库
#DEFINES += _PSV_TEST

!contains(DEFINES,_PSV_TEST){
DEFINES += _PSVLIB_DLL
}

contains(DEFINES,_PSVLIB_DLL){
NAME = psv_lib
TEMPLATE = lib
}
!contains(DEFINES,_PSVLIB_DLL){
message(TTTTTTTTTTTTTTTTTT)
NAME = psv_test
TEMPLATE = app
SOURCES += test/main.cpp
SOURCES += test/dialog_test.cpp
SOURCES += source/psv_test.cpp
HEADERS += include/psv_test.h
HEADERS += test/dialog_test.h
FORMS += test/dialog_test.ui
INCLUDEPATH += ./test
}

TARGET = $${NAME}
CONFIG	+= qt
#CONFIG	+=  warn_on
#CONFIG	+=  debug_and_release
QT += gui
QT += core
INCLUDEPATH += ./include

win32 {
DESTDIR  = ./bin
}else {
DESTDIR  = ./release/bin
}

win32 {
    CONFIG(debug, debug|release){
        OBJECTS_DIR = ./TEMP/$${TARGET}/debug
    }
    CONFIG(release, debug|release){
        OBJECTS_DIR = ./TEMP/$${TARGET}/release
    }
    DESTDIR = ./bin
contains(DEFINES,_PSVLIB_DLL){
    DESTDIR = ./bin
}
} else {
contains(DEFINES,_PSVLIB_DLL){
    DESTDIR  = ./release/lib
}else{
    DESTDIR  = ./release/bin
}
    OBJECTS_DIR = ./TEMP/$${TARGET}
}

#DLLDESTDIR += D:\workroot\lib

UI_DIR      = $${OBJECTS_DIR}/uic
MOC_DIR     = $${OBJECTS_DIR}/moc
RCC_DIR     = $${OBJECTS_DIR}/rcc
INCLUDEPATH += $${OBJECTS_DIR}/uic

SOURCES += source/psv_graphicsview.cpp
SOURCES += source/psv_buttonitem.cpp
SOURCES += source/psv_treeitem.cpp
SOURCES += source/psv_graphicsscene.cpp
SOURCES += source/psv_histogramitem.cpp
SOURCES += source/psv_define.cpp
SOURCES += source/psv_public.cpp
SOURCES += source/psv_circularindicatoritem.cpp
SOURCES += source/psv_axisitem.cpp
SOURCES += source/psv_tableitem.cpp
SOURCES += source/psv_pie3item.cpp
SOURCES += source/psv_sectoritem.cpp
SOURCES += source/psv_chartitem.cpp
SOURCES += source/psv_charttimeitem.cpp
SOURCES += source/psv_axisleftitem.cpp
SOURCES += source/psv_axisrightitem.cpp
SOURCES += source/psv_axisdownitem.cpp
SOURCES += source/psv_axisupitem.cpp
SOURCES += source/psv_item.cpp
SOURCES += source/psv_chartdatetimeitem.cpp
SOURCES += source/psv_chartrealitem.cpp
SOURCES += source/psv_charthistogramitem.cpp
SOURCES += source/psv_chartareaitem.cpp
SOURCES += source/psv_tablewidgetitem.cpp
SOURCES += source/psv_painterpathitem.cpp
SOURCES += source/psv_verticalindicatoritem.cpp
SOURCES += source/psv_chartbaritem.cpp
SOURCES += source/psv_levelitem.cpp

HEADERS += include/psv_graphicsview.h
HEADERS += include/psv_buttonitem.h
HEADERS += include/psv_treeitem.h
HEADERS += include/psv_graphicsscene.h
HEADERS += include/psv_histogramitem.h
HEADERS += include/psv_public.h
HEADERS += include/psv_define.h
HEADERS += include/psv_circularindicatoritem.h
HEADERS += include/psv_axisitem.h
HEADERS += include/psv_tableitem.h
HEADERS += include/psv_pie3item.h
HEADERS += include/psv_sectoritem.h
HEADERS += include/psv_chartitem.h
HEADERS += include/psv_charttimeitem.h
HEADERS += include/psv_axisleftitem.h
HEADERS += include/psv_axisrightitem.h
HEADERS += include/psv_axisdownitem.h
HEADERS += include/psv_axisupitem.h
HEADERS += include/psv_item.h
HEADERS += include/psv_chartdatetimeitem.h
HEADERS += include/psv_chartrealitem.h
HEADERS += include/psv_charthistogramitem.h
HEADERS += include/psv_chartareaitem.h
HEADERS += include/psv_tablewidgetitem.h
HEADERS += include/psv_painterpathitem.h
HEADERS += include/psv_verticalindicatoritem.h
HEADERS += include/psv_chartbaritem.h
HEADERS += include/psv_levelitem.h
HEADERS += include/psvlib.h
