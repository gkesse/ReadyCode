TEMPLATE = app
TARGET = rdcpp
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
RCC_DIR = build
CONFIG += console debug gnu++11
QT += widgets sql printsupport

QMAKE_CXXFLAGS +=\
    -Wno-unused-parameter \
    -Wno-deprecated-declarations

include(C:\Users\Admin\Downloads\Programs\ReadyLib\dev\qcustomplot\2.1.0\GQCustomPlot.pri)

LIBS +=\
    -LC:\msys64\mingw32\lib \
    -lgsl -lgslcblas -lm \
    -lopencv_gapi -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_bgsegm \
    -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face \
    -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform \
    -lopencv_line_descriptor -lopencv_mcc -lopencv_ovis -lopencv_quality -lopencv_rapid \
    -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo \
    -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow \
    -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text \
    -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_xfeatures2d -lopencv_shape \
    -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_dnn -lopencv_xobjdetect \
    -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann \
    -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core \
    -lcurl -lws2_32 \

INCLUDEPATH +=\
    C:\msys64\mingw32\include \
    C:\msys64\mingw32\include\opencv4 \
    C:\Users\Admin\Downloads\RLib\glad\include \
    ..\code\src \

SOURCES +=\
    ..\code\src\*.cpp \

HEADERS +=\
    ..\code\src\*.h \
    