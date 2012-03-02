TARGET = declarative_multimedia
TARGETPATH = QtMultimedia

include(../qimportbase.pri)

QT += declarative quick network multimedia-private

DESTDIR = $$QT.multimedia.imports/$$TARGETPATH
target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

LIBS += -lQtMultimediaQuick_p

HEADERS += \
        qdeclarativeaudio_p.h \
        qdeclarativemediabase_p.h \
        qdeclarativemediametadata_p.h \
        qdeclarativevideooutput_p.h \
        qsgvideonode_i420.h \
        qsgvideonode_rgb.h \
        qdeclarativeradio_p.h \
        qdeclarativeradiodata_p.h \
        qdeclarativecamera_p.h \
        qdeclarativecameracapture_p.h \
        qdeclarativecamerarecorder_p.h \
        qdeclarativecameraexposure_p.h \
        qdeclarativecameraflash_p.h \
        qdeclarativecamerafocus_p.h \
        qdeclarativecameraimageprocessing_p.h \
        qdeclarativecamerapreviewprovider_p.h \
        qdeclarativetorch_p.h \
        qdeclarativeaudio_p_4.h \
        qdeclarativemediabase_p_4.h

SOURCES += \
        multimedia.cpp \
        qdeclarativeaudio.cpp \
        qdeclarativemediabase.cpp \
        qdeclarativevideooutput.cpp \
        qsgvideonode_i420.cpp \
        qsgvideonode_rgb.cpp \
        qdeclarativeradio.cpp \
        qdeclarativeradiodata.cpp \
        qdeclarativecamera.cpp \
        qdeclarativecameracapture.cpp \
        qdeclarativecamerarecorder.cpp \
        qdeclarativecameraexposure.cpp \
        qdeclarativecameraflash.cpp \
        qdeclarativecamerafocus.cpp \
        qdeclarativecameraimageprocessing.cpp \
        qdeclarativecamerapreviewprovider.cpp \
        qdeclarativetorch.cpp \
        qdeclarativemediabase_4.cpp \
        qdeclarativeaudio_4.cpp

OTHER_FILES += \
    Video_4.qml \
    Video.qml

qmldir.files += $$PWD/qmldir $$PWD/Video.qml $$PWD/Video_4.qml
qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

# another copy of the qmldir file so the old import works
OLDQMLDIRFILE = $${_PRO_FILE_PWD_}/qmldir.qtmultimediakit
oldcopy2build.input = OLDQMLDIRFILE
oldcopy2build.output = $$QT.multimedia.imports/Qt/multimediakit/qmldir
!contains(TEMPLATE_PREFIX, vc):oldcopy2build.variable_out = PRE_TARGETDEPS
oldcopy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
oldcopy2build.name = COPY ${QMAKE_FILE_IN}
oldcopy2build.CONFIG += no_link
# `clean' should leave the build in a runnable state, which means it shouldn't delete qmldir
oldcopy2build.CONFIG += no_clean
QMAKE_EXTRA_COMPILERS += oldcopy2build

INSTALLS += target qmldir
