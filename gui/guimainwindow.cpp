/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "guimainwindow.h"
#include "core/coreschema.h"
#include "core/coremachine.h"
#include "draw/drawnmodule.h"
#include "draw/drawnschema.h"
#include "draw/drawninput.h"
#include "draw/drawnoutput.h"
#include "draw/drawnwire.h"
#include "ui_guimainwindow.h"
#include "guimenufile.h"
#include "guischemascene.h"
#include "guimodulelibraryview.h"
#include "oscilloscope/guioscilloscopedock.h"
#include "guistyle.h"

#include <QSettings>
#include <stdexcept>

// Audio part
#include "audio/audiofifobuffer.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

GuiMainWindow::GuiMainWindow(QSettings *settings, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GuiMainWindow),
      mSettings(settings),
      mSchema(nullptr), mCoreMachine(),
      mAudioOutputBuffer(nullptr), mAudioOutput(nullptr),
      mCurrentFilePath("")
{
    // Workscheet view
    ui->setupUi(this);

    // Prepare audio device & buffer
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format = device.preferredFormat();
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    mAudioOutput = new QAudioOutput(device, format);
    mAudioOutputBuffer = new AudioFifoBuffer(format.byteOrder());
    mAudioOutputBuffer->open(QIODevice::ReadOnly);
    mAudioOutput->start(mAudioOutputBuffer);
    mAudioOutputBuffer->fill(0, mAudioOutput->periodSize()/2);
    mSampleRate = format.sampleRate();
    mCoreMachine.setStepTime(1.0f/float(mSampleRate));
    ui->speakerOutputComboBox->setAudioBuffer(mAudioOutputBuffer);

    // Create menu
    GuiMenuFile *menuFile = new GuiMenuFile(this, mSettings);
    ui->menubar->addMenu(menuFile);

    // Toolbar actions
    connect(ui->actionOscilloscope, &QAction::triggered, this, &GuiMainWindow::handleOscilloscope);

    // Start with a new file
    menuFile->handleFileNew();
}

GuiMainWindow::~GuiMainWindow()
{
    mAudioOutput->stop();
    mCoreMachine.stop();
    if (mSchema)
        delete mSchema;

    delete mAudioOutputBuffer;
    delete mAudioOutput;
    delete ui;
}

bool GuiMainWindow::changeSchema(DrawnSchema *schema)
{
    if (mSchema == schema)
        return true;

    if (mSchema) {
        // TODO: Add here save / discard actions if not saved schema (return false if user cancels)

        // Stop machine before any operation
        mCoreMachine.stop();

        emit schemaChanged(nullptr);

        // Delete old schema

        // TODO : Use above signal instead
        ui->speakerOutputComboBox->setSchema(nullptr); // TODO: ComboBox should be connected to view rather than schema
        ui->schemaView->setSchema(nullptr);
        ui->modulesLibraryView->setFactory(nullptr);
        delete mSchema;
        mSchema = nullptr;
    }

    mSchema = schema;

    if (mSchema) {
        emit schemaChanged(mSchema);

        // TODO : Use above signal instead
        ui->modulesLibraryView->setFactory(mSchema->getModuleFactory());
        ui->speakerOutputComboBox->setSchema(mSchema); // TODO: ComboBox should be connected to view rather than schema
        ui->schemaView->setSchema(mSchema);
        ui->schemaView->setTransform(QTransform());
        ui->schemaView->scale(ui->modulesLibraryView->getScale(), ui->modulesLibraryView->getScale());

        // Restart machine
        mCoreMachine.setSchema(mSchema->core());
        mCoreMachine.start();
    }

    return true;
}

void GuiMainWindow::handleOscilloscope()
{
    GuiOscilloscopeDock *dock = new GuiOscilloscopeDock(ui->schemaView, mSampleRate);
    addDockWidget(Qt::RightDockWidgetArea, dock);
}
