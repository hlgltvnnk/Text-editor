#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <QFileSystemModel>
#include <QDebug>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QMap>
#include "textedit.h"

#define TOOLBARSIZE 40

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString currentFile;
    QMap <QString, TextEdit *> Files;

    void chooseDir();
    void chooseFile();
    void saveFileAs();
    void changeToolBarSize();
    void setTreeView(QString path);
    void openFile(QString filename);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *m_DirList {new QFileSystemModel(this)};

public slots:
    void FileClicked(QModelIndex index);
    void resizeEvent(QResizeEvent *event);
    void on_actionLogo_triggered();
    
    //ЕНТО СДЕЛАЛЬ Я ВОТ ДА ВОТ ТАК ВОТ ДА ДА
    void copyString();
    void cutString();
    void pasteString();
    //END 
};

#endif // MAINWINDOW_H
