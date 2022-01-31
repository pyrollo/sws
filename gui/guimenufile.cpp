#include "guimenufile.h"
#include "guimainwindow.h"
#include "draw/drawnschema.h"

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QSettings>
#include <QTextStream>
#include <QApplication>

#include "file/fileserializer.h"
#include "file/filedeserializer.h"

GuiMenuFile::GuiMenuFile(GuiMainWindow *mainWindow, QSettings *settings):
    QMenu(tr("&File"), mainWindow), mMainWindow(mainWindow), mSettings(settings), mSettingName("RecentFiles")
{
    updateItems();
    mMaxRecentFiles = 10;
}

GuiMenuFile::~GuiMenuFile()
{
}

void GuiMenuFile::updateItems()
{
    clear();

    QAction *action;

    action = addAction("New");
    connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileNew);
    action = addAction("Open");
    connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileOpen);
    action = addAction("Save");
    connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileSave);
    action = addAction("Save as...");
    connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileSaveAs);

    addSeparator();

    QStringList recentFiles = mSettings->value(mSettingName).toStringList();
    int n = 0;
    for (QString filePath: recentFiles) {
        n++;
        QAction *action = addAction(tr("&%1 %2").arg(n).arg(QFileInfo(filePath).fileName()));
        connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileOpenRecent);
        action->setData(filePath);
        action->setVisible(true);
    }

    if (n)
         addSeparator();

    action = addAction("Quit");
    connect(action, &QAction::triggered, this, &GuiMenuFile::handleFileQuit);
}

void GuiMenuFile::setCurrentFilePath(QString filePath)
{
    mCurrentFilePath = filePath;

    QStringList recentFiles = mSettings->value(mSettingName).toStringList();
    recentFiles.prepend(filePath);
    recentFiles.removeDuplicates();
    while (recentFiles.size() > mMaxRecentFiles)
        recentFiles.removeLast();

    mSettings->setValue(mSettingName, recentFiles);
    updateItems();
}

void GuiMenuFile::loadFile(QString filePath)
{
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

    if (!mMainWindow->changeSchema(schema))
        delete schema;
    else
        setCurrentFilePath(filePath);
}

void GuiMenuFile::saveFile(QString filePath)
{
    QFile file(filePath);

    FileSerializer fs(mMainWindow->getSchema());

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << fs.serialize();
        file.close();
        setCurrentFilePath(filePath);
    }
}

void GuiMenuFile::handleFileNew()
{
    DrawnSchema *schema = new DrawnSchema();
    if (!mMainWindow->changeSchema(schema))
        delete schema;
}

void GuiMenuFile::handleFileOpen()
{
    // TODO: Factorize with handleFileNew
    QString filePath = QFileDialog::getOpenFileName(this,
        tr("Open file"), QString(), tr("SWS files (*.sws)"));

    loadFile(filePath);
}

void GuiMenuFile::handleFileSave()
{
    if (mCurrentFilePath == "")
        handleFileSaveAs();
    else
        saveFile(mCurrentFilePath);
}

void GuiMenuFile::handleFileSaveAs()
{
    QString filePath = QFileDialog::getSaveFileName(this,
        tr("Save file"), QString(), tr("SWS files (*.sws)"));

    if (filePath != "") {
        // TODO: Add .sws extension if none specified
        saveFile(filePath);
     }
}

void GuiMenuFile::handleFileOpenRecent()
{
    // TODO: Would be better to use a QSignalMapper
    QAction* action = qobject_cast<QAction *>(sender());
    if (action != 0)
    {
        QVariant data = action->data();
        printf("Open recent %s\n", data.toString().toStdString().c_str()); fflush(stdout);
        loadFile(data.toString());
    }
}

void GuiMenuFile::handleFileQuit()
{
    if (mMainWindow->changeSchema(nullptr))
        QApplication::quit();
}
