QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qimagematconvert.cpp \
    ../mat_qimage_convert.cpp

HEADERS += \
    ../mat_qimage_convert.h

# MinGW32
INCLUDEPATH += C:/opencv/mingw730/include
LIBS += C:/opencv/mingw730/lib/libopencv_*.a
