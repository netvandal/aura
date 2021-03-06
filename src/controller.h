/*
 * This file is part of aura
 *
 * Copyright (C) 2012 Igalia S.L.
 *
 * Contact: Miguel Gómez <magomez@igalia.com>
 *          Xabier Rodriguez Calvar <xrcalvar@igalia.com>
 *          Víctor Jáquez <vjaquez@igalia.com>
 *          Michele Tameni <michele@tameni.it>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDeclarativeItem>
#include <QTimer>
#include "pipeline.h"

class Controller : public QDeclarativeItem
{
    Q_OBJECT

 public:
    Q_PROPERTY(bool recording
               READ recording
               WRITE setRecording
               NOTIFY recordingChanged)
    Q_PROPERTY(QString videoEffect
               READ videoEffect
               WRITE setVideoEffect
               NOTIFY videoEffectChanged)
    Q_PROPERTY(ControllerSettings::ColorFilter colorFilter
               READ colorFilter
               WRITE setColorFilter
               NOTIFY colorFilterChanged)
    Q_PROPERTY(ControllerSettings::Device device
               READ device
               WRITE setDevice
               NOTIFY deviceChanged)
    Q_PROPERTY(QString savedFileName
               READ savedFileName
               NOTIFY savedFileNameChanged)
    Q_PROPERTY(bool pipelineStarting
               READ pipelineStarting
               WRITE setPipelineStarting
               NOTIFY pipelineStartingChanged)
    Q_PROPERTY(bool pipelineReady
               READ pipelineReady
               WRITE setPipelineReady
               NOTIFY pipelineReadyChanged)
    Q_PROPERTY(QString recordedTime
               READ recordedTime
               NOTIFY recordedTimeChanged)

    Controller(QDeclarativeItem *parent = 0);
    ~Controller();
    void setupEffects();

    // user to set user defined values
    void setResolution(const Pipeline::Resolution value);
    void setZoom(const double value);

    Pipeline::Resolution resolution() {return m_currentResolution;};
    double zoom() {return m_currentZoom;};
    ControllerSettings::ColorFilter colorFilter() {return m_currentColorFilter;};
    QString videoEffect() {return m_currentVideoEffect;};
    ControllerSettings::Device device() {return m_currentDevice;};

    bool recording() { return m_recording; };
    QString savedFileName();
    bool pipelineStarting() {return m_pipelineStarting;};
    bool pipelineReady() {return m_pipelineReady;};
    QString recordedTime();

public slots:
    void startPipeline();
    void stopPipeline();
    void pausePipeline();
    void startRecording();
    void stopRecording();
    void captureImage();
    void shutterClicked();
    void cameraShutterClicked();
    void setRecording(bool recording);
    void setVideoEffect(const QString &value);
    void setColorFilter(const ControllerSettings::ColorFilter value);
    void setDevice(const ControllerSettings::Device value);
    void setPipelineStarting(bool pipelineStarting);
    void setPipelineReady(bool pipelineReady);
    void setRecordedTime(int recordedTime);
    void delayedPipelineStop(bool idle);

signals:
    void recordingChanged(bool recording);
    void videoEffectChanged(const QString &effectName);
    void colorFilterChanged(const ControllerSettings::ColorFilter value);
    void deviceChanged(const ControllerSettings::Device value);
    void savedFileNameChanged(const QString &filename);
    void pipelineStartingChanged(bool pipelineStarting);
    void pipelineReadyChanged(bool pipelineReady);
    void recordedTimeChanged(const QString &recordedTime);

 private slots:
    void resourcesLost();
    void idleChanged(bool isIdle);
    void pipelineStartingFinished();
    void recordingTimerTimeout();

 private:
    Pipeline *m_pipeline;
    bool m_recording;
    bool m_pipelineStarting;
    bool m_pipelineReady;
    int m_recordedTime;
    QTimer m_recordingTimer;
    // current config
    double m_currentZoom;
    Pipeline::Resolution m_currentResolution;
    ControllerSettings::ColorFilter m_currentColorFilter;
    QString m_currentVideoEffect;
    ControllerSettings::Device m_currentDevice;
};
#endif
