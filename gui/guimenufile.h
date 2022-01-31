#ifndef GUIMENUFILE_H
#define GUIMENUFILE_H

#include <QMenu>

class QSettings;
class GuiMainWindow;

class GuiMenuFile: public QMenu
{
public:
    GuiMenuFile(GuiMainWindow *mainWindow, QSettings *settings);
    ~GuiMenuFile();

public slots:
    void handleFileNew();
    void handleFileOpen();
    void handleFileSave();
    void handleFileSaveAs();
    void handleFileOpenRecent();
    void handleFileQuit();

private:
    GuiMainWindow *mMainWindow;
    QSettings *mSettings;
    QString mSettingName;
    QString mCurrentFilePath;
    int mMaxRecentFiles;

    void setCurrentFilePath(QString filePath);
    void updateItems();
    void loadFile(QString filePath);
    void saveFile(QString filePath);
};

#endif // GUIMENUFILE_H
