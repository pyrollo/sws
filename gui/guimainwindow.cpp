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
#include "file/fileserializer.h"
#include "file/filedeserializer.h"
#include "ui_guimainwindow.h"
#include "guischemascene.h"
#include "guimodulelibraryview.h"
#include "guistyle.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "audio/audiofifobuffer.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <stdexcept>

GuiMainWindow::GuiMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GuiMainWindow),
      mSchema(nullptr), mCoreMachine(),
      mAudioOutputBuffer(nullptr), mAudioOutput(nullptr),
      mCurrentFilePath("")
{
    // Workscheet view
    ui->setupUi(this);
    ui->schemaView->setProbeWidget(ui->probeLabel);

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
    mCoreMachine.setStepTime(1.0f/float(format.sampleRate()));
    ui->speakerOutputComboBox->setAudioBuffer(mAudioOutputBuffer);

    // Connect oscilloscope
    ui->speakerOutputComboBox->setOscilloscopeBuffer(ui->oscilloscope->getSampleBuffer());

    // Menu actions
    connect(ui->actionNew,    &QAction::triggered, this, &GuiMainWindow::handleFileNew);
    connect(ui->actionOpen,   &QAction::triggered, this, &GuiMainWindow::handleFileOpen);
    connect(ui->actionSave,   &QAction::triggered, this, &GuiMainWindow::handleFileSave);
    connect(ui->actionSaveAs, &QAction::triggered, this, &GuiMainWindow::handleFileSaveAs);
    connect(ui->actionQuit,   &QAction::triggered, this, &GuiMainWindow::handleFileQuit);

    // Start with a new file
    handleFileNew();
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

        // Delete old schema
        ui->speakerOutputComboBox->setSchema(nullptr); // TODO: ComboBox should be connected to view rather than schema
        ui->schemaView->setSchema(nullptr);
        ui->modulesLibraryView->setFactory(nullptr);
        delete mSchema;
        mSchema = nullptr;
    }

    mSchema = schema;

    if (mSchema) {
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

void GuiMainWindow::handleFileNew()
{
    DrawnSchema *schema = new DrawnSchema();
    if (!changeSchema(schema))
        delete schema;
}

void GuiMainWindow::handleFileOpen()
{
    // TODO: Factorize with handleFileNew

    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open file"), QString(), tr("SWS files (*.sws)"));

    if (filePath == "")
        return;

    // TODO: manage file access errors

    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    // TODO: manage file format errors

    FileDeserializer deserializer(data);
    DrawnSchema *schema = deserializer.deserializeToDrawnSchema();

    if (!changeSchema(schema))
        delete schema;
    else
        mCurrentFilePath = filePath;
}

void GuiMainWindow::handleFileSave()
{
    if (mCurrentFilePath == "") {
        handleFileSaveAs();
        return;
    }

    QFile file(mCurrentFilePath);
    FileSerializer fs(mSchema);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << fs.serialize();
        file.close();
    }
}

void GuiMainWindow::handleFileSaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this,
        tr("Save file"), QString(), tr("SWS files (*.sws)"));

    if (filePath != "") {
        // TODO: Add .sws extension if none specified
        mCurrentFilePath = filePath;
        handleFileSave();
     }
}

void GuiMainWindow::handleFileQuit()
{
    if (changeSchema(nullptr))
        QApplication::quit();
}
