QT += qml quick widgets charts core sql network

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS 
QMAKE_CFLAGS = -fpermissive
QMAKE_CXXFLAGS = -fpermissive
QMAKE_LFLAGS = -fpermissive

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/aladdin_client.cpp \
    src/wrapper_client.pb.cc \
    src/udp/ofFileUtils.cpp \
    src/udp/ofLog.cpp \
    src/udp/ofUtils.cpp \
    src/udp/ofxNetworkUtils.cpp \
    src/udp/ofxUDPManager.cpp \ 
    src/aladdin_maker.cpp \
    src/fingertip_search.cpp \
    src/jpg_http.cpp \
    src/youdao_api.cpp \
    src/sha256.cpp \
    src/utils.cpp \
    src/data_listmodel.cpp \
    src/config/cls_config.cpp

HEADERS += \
    src/miniaudio.h \
    src/aladdin_client.h \
    src/wrapper_client.pb.h \
    src/udp/ofConstants.h \
    src/udp/ofFileUtils.h \
    src/udp/ofLog.h \
    src/udp/ofUtils.h \
    src/udp/ofxNetwork.h \
    src/udp/ofxNetworkUtils.h \
    src/udp/ofxUDPManager.h \
    src/udp/ofxUDPSettings.h \
    src/aladdin_maker.h \
    src/aladdin_client.h \
    src/fingertip_search.h \
    src/jpg_http.h \
    src/youdao_api.h \
    src/sha256.h \
    src/utils.h \
    src/data_listmodel.h \
    src/config/cls_config.h

INCLUDEPATH += \
    src/ \
    /root/aladin_client/3rdparty/boost/include \
    /root/aladin_client/3rdparty/protobuf/include \
    /root/aladin_client/3rdparty/utf8/include \
    src/udp/ \
    src/config \
    /usr/include/glib-2.0 \
    /usr/lib/aarch64-linux-gnu/glib-2.0/include \
    src/lib_stardict \
    src/lib_stardict/Private \
    src/offline_sss_host/common \
    src/offline_sss_host/include


SourceDir = ./src/lib_stardict \
    ./src/offline_sss_host/common

for(var, SourceDir) {
    SOURCES += $$files($$join(var, , , /*.cpp), true)
    HEADERS += $$files($$join(var, , , /*.h), true)
    HEADERS += $$files($$join(var, , , /*.hpp), true)
}

LIBS += -L/root/aladin_client/3rdparty/boost/lib -lboost_filesystem -lboost_system \
        -L/root/aladin_client/3rdparty/protobuf/lib -lprotobuf -lprotobuf-lite \
        -L./thirdparty/lib -ljson_libmt -lhiredis \
	-ldl -lm -lpthread -lglib-2.0 -lz \
        -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc \
	-lrknn_api

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
