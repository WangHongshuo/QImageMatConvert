QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_qimagematconvert.cpp

# MinGW32

INCLUDEPATH += C:/opencv/mingw730/include \
            += ../mat_qimage_convert.h
LIBS += C:/opencv/mingw730/lib/libopencv_*.a
