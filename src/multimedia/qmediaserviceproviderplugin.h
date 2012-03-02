/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QMEDIASERVICEPROVIDERPLUGIN_H
#define QMEDIASERVICEPROVIDERPLUGIN_H

#include <QtCore/qstringlist.h>
#include <QtCore/qplugin.h>
#include <QtCore/qfactoryinterface.h>
#include <qtmedianamespace.h>
#include <qtmultimediadefs.h>

#ifdef Q_MOC_RUN
# pragma Q_MOC_EXPAND_MACROS
#endif

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Multimedia)

class QMediaService;

class QMediaServiceProviderHintPrivate;
class Q_MULTIMEDIA_EXPORT QMediaServiceProviderHint
{
public:
    enum Type { Null, ContentType, Device, SupportedFeatures };

    enum Feature {
        LowLatencyPlayback = 0x01,
        RecordingSupport = 0x02,
        StreamPlayback = 0x04,
        VideoSurface = 0x08
    };
    Q_DECLARE_FLAGS(Features, Feature)

    QMediaServiceProviderHint();
    QMediaServiceProviderHint(const QString &mimeType, const QStringList& codecs);
    QMediaServiceProviderHint(const QByteArray &device);
    QMediaServiceProviderHint(Features features);
    QMediaServiceProviderHint(const QMediaServiceProviderHint &other);
    ~QMediaServiceProviderHint();

    QMediaServiceProviderHint& operator=(const QMediaServiceProviderHint &other);

    bool operator == (const QMediaServiceProviderHint &other) const;
    bool operator != (const QMediaServiceProviderHint &other) const;

    bool isNull() const;

    Type type() const;

    QString mimeType() const;
    QStringList codecs() const;

    QByteArray device() const;

    Features features() const;

    //to be extended, if necessary

private:
    QSharedDataPointer<QMediaServiceProviderHintPrivate> d;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QMediaServiceProviderHint::Features)


struct Q_MULTIMEDIA_EXPORT QMediaServiceProviderFactoryInterface : public QFactoryInterface
{
    virtual QStringList keys() const = 0;
    virtual QMediaService* create(QString const& key) = 0;
    virtual void release(QMediaService *service) = 0;
};

#define QMediaServiceProviderFactoryInterface_iid \
    "com.nokia.Qt.QMediaServiceProviderFactoryInterface/1.0"
Q_DECLARE_INTERFACE(QMediaServiceProviderFactoryInterface, QMediaServiceProviderFactoryInterface_iid)


struct Q_MULTIMEDIA_EXPORT QMediaServiceSupportedFormatsInterface
{
    virtual ~QMediaServiceSupportedFormatsInterface() {}
    virtual QtMultimedia::SupportEstimate hasSupport(const QString &mimeType, const QStringList& codecs) const = 0;
    virtual QStringList supportedMimeTypes() const = 0;
};

#define QMediaServiceSupportedFormatsInterface_iid \
    "com.nokia.Qt.QMediaServiceSupportedFormatsInterface/1.0"
Q_DECLARE_INTERFACE(QMediaServiceSupportedFormatsInterface, QMediaServiceSupportedFormatsInterface_iid)


struct Q_MULTIMEDIA_EXPORT QMediaServiceSupportedDevicesInterface
{
    virtual ~QMediaServiceSupportedDevicesInterface() {}
    virtual QList<QByteArray> devices(const QByteArray &service) const = 0;
    virtual QString deviceDescription(const QByteArray &service, const QByteArray &device) = 0;
};

#define QMediaServiceSupportedDevicesInterface_iid \
    "com.nokia.Qt.QMediaServiceSupportedDevicesInterface/1.0"
Q_DECLARE_INTERFACE(QMediaServiceSupportedDevicesInterface, QMediaServiceSupportedDevicesInterface_iid)



struct Q_MULTIMEDIA_EXPORT QMediaServiceFeaturesInterface
{
    virtual ~QMediaServiceFeaturesInterface() {}
    virtual QMediaServiceProviderHint::Features supportedFeatures(const QByteArray &service) const = 0;
};


#define QMediaServiceFeaturesInterface_iid \
    "com.nokia.Qt.QMediaServiceFeaturesInterface/1.0"
Q_DECLARE_INTERFACE(QMediaServiceFeaturesInterface, QMediaServiceFeaturesInterface_iid)


class Q_MULTIMEDIA_EXPORT QMediaServiceProviderPlugin : public QObject, public QMediaServiceProviderFactoryInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaServiceProviderFactoryInterface:QFactoryInterface)

public:
    virtual QStringList keys() const = 0;
    virtual QMediaService* create(const QString& key) = 0;
    virtual void release(QMediaService *service) = 0;
};

/*!
    Service with support for media playback
    Required Controls: QMediaPlayerControl
    Optional Controls: QMediaPlaylistControl, QAudioDeviceControl
    Video Output Controls (used by QWideoWidget and QGraphicsVideoItem):
                        Required: QVideoOutputControl
                        Optional: QVideoWindowControl, QVideoRendererControl, QVideoWidgetControl
*/
#define Q_MEDIASERVICE_MEDIAPLAYER "com.nokia.qt.mediaplayer"

/*!
   Service with support for recording from audio sources
   Required Controls: QAudioDeviceControl
   Recording Controls (QMediaRecorder):
                        Required: QMediaRecorderControl
                        Recommended: QAudioEncoderControl
                        Optional: QMediaContainerControl
*/
#define Q_MEDIASERVICE_AUDIOSOURCE "com.nokia.qt.audiosource"

/*!
    Service with support for camera use.
    Required Controls: QCameraControl
    Optional Controls: QCameraExposureControl, QCameraFocusControl, QCameraImageProcessingControl
    Still Capture Controls: QCameraImageCaptureControl
    Video Capture Controls (QMediaRecorder):
                        Required: QMediaRecorderControl
                        Recommended: QAudioEncoderControl, QVideoEncoderControl, QMediaContainerControl
    Viewfinder Video Output Controls (used by QCameraViewfinder and QGraphicsVideoItem):
                        Required: QVideoOutputControl
                        Optional: QVideoWindowControl, QVideoRendererControl, QVideoWidgetControl
*/
#define Q_MEDIASERVICE_CAMERA "com.nokia.qt.camera"

/*!
    Service with support for radio tuning.
    Required Controls: QRadioTunerControl
    Recording Controls (Optional, used by QMediaRecorder):
                        Required: QMediaRecorderControl
                        Recommended: QAudioEncoderControl
                        Optional: QMediaContainerControl
*/
#define Q_MEDIASERVICE_RADIO "com.nokia.qt.radio"

/*!
    Service with support for decoding audio.
    Required Controls: QAudioDecoderControl
    Optional: that streams control
*/
#define Q_MEDIASERVICE_AUDIODECODER "com.nokia.qt.audiodecode"



QT_END_NAMESPACE

QT_END_HEADER



#endif  // QMEDIASERVICEPROVIDERPLUGIN_H
