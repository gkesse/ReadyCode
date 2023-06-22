TEMPLATE = app
TARGET = rdv_cpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug gnu++11
QT += widgets printsupport xml

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations \

INCLUDEPATH +=\
    ..\code\src\manager \
    ..\code\src\libs\include \
    ..\code\src\libs\include\libxml2 \
    ..\code\src\libs\include\b64 \
    ..\code\src\libs\include\base64 \

LIBS +=\
    -L..\code\src\libs\lib \
    -lws2_32 -lxml2 -lb64c -lbase64 \


SOURCES +=\
    $$files(..\code\src\*.cpp) \
    $$files(..\code\src\manager\*.cpp) \
    
HEADERS +=\
    $$files(..\code\src\manager\*.h) \

FORMS +=\
    $$files(..\code\src\manager\*.ui) \

