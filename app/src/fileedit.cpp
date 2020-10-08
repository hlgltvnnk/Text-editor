#include "MainWindow.h"
#include "ui_MainWindow.h"

void MainWindow::openFile(QString filename) {
    TextEdit *file = new TextEdit(filename);
    Files.insert(filename, file);
    ui->TextEditor->setPlainText(Files[filename]->text.toPlainText());
    currentFile = filename;
}

void MainWindow::chooseDir() {
    QString dir = QFileDialog::getExistingDirectory(this, "Open Directory", ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dir.isNull() && QDir(dir).exists() && QDir(dir).isReadable()) {
        setTreeView(dir);
        ui->FileTree->setCurrentIndex(1);
    }
}

void MainWindow::chooseFile() {
    QString file = QFileDialog::getOpenFileName(this,tr("Open Document"),
                               QDir::currentPath(), tr("text files (*.txt)"));

    if (!file.isNull() && QFileInfo(file).exists() && QFileInfo(file).isReadable()) {
        setTreeView(QFileInfo(file).absolutePath());
        openFile(file);
        ui->FileTree->setCurrentIndex(1);
    }
}

bool isLegalFilePath(QString path)
{
    // Anything following the raw filename prefix should be legal.
    if (path.left(4)=="\\\\?\\")
        return true;

    // Windows filenames are not case sensitive.
    path = path.toUpper();

    // Trim the drive letter off
    if (path[1]==':' && (path[0]>='A' && path[0]<='Z'))
        path = path.right(path.length()-2);

    QString illegal="<>:\"|?*";

    foreach (const QChar& c, path)
    {
        // Check for control characters
         if (c.toLatin1() > 0 && c.toLatin1() < 32)
            return false;

        // Check for illegal characters
        if (illegal.contains(c))
            return false;
    }

    // Check for device names in filenames
    static QStringList devices;

    if (!devices.count())
        devices << "CON" << "PRN" << "AUX" << "NUL" << "COM0" << "COM1" << "COM2"
                << "COM3" << "COM4" << "COM5" << "COM6" << "COM7" << "COM8" << "COM9" << "LPT0"
                << "LPT1" << "LPT2" << "LPT3" << "LPT4" << "LPT5" << "LPT6" << "LPT7" << "LPT8"
                << "LPT9";

    const QFileInfo fi(path);
    const QString basename = fi.baseName();

    foreach (const QString& s, devices)
        if (basename == s)
            return false;

    // Check for trailing periods or spaces
    if (path.right(1)=="." || path.right(1)==" ")
        return false;

    // Check for pathnames that are too long (disregarding raw pathnames)
    if (path.length()>260)
        return false;

    // Exclude raw device names
    if (path.left(4)=="\\\\.\\")
        return false;

    // Since we are checking for a filename, it mustn't be a directory
    if (path.right(1)=="\\")
        return false;

    return true;
}

void MainWindow::saveFileAs() {
   bool ok;
   if (!currentFile.isEmpty()) {
       QString dir = QFileDialog::getExistingDirectory(this, "Choose Directory", ".",
            QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

       if (!dir.isNull() && QDir(dir).exists() && QDir(dir).isReadable()) {
           QString filename = QInputDialog::getText(this, tr("Enter FileName"),tr("Write file name:"), QLineEdit::Normal,"", &ok);
           QString tmp = dir + "/" +  filename + ".txt";
           if (ok && !filename.isEmpty() && isLegalFilePath(tmp)) {
               openFile(tmp);
               Files[currentFile]->saveFile(ui->TextEditor->toPlainText());
            }
           else  QMessageBox::critical(this, "", "Invalid filename");
       }
    }
   else  QMessageBox::critical(this, "", "Choose file before saving");
}

void MainWindow::FileClicked(QModelIndex index) {
    QFile file(m_DirList->filePath(index));
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        file.close();
        openFile(m_DirList->filePath(index));
    }
}

void MainWindow::on_actionLogo_triggered()
{
    delete ui->actionLogo->menu();
    QMenu * menu = new QMenu(this);
    QAction * openFileAction = new QAction("Open file", this);
    QAction * openDirAction = new QAction("Open folder", this);
    QAction * saveAction = new QAction("Save", this);
    QAction * saveAsAction = new QAction("Save as", this);

    connect(openDirAction, &QAction::triggered, this, &MainWindow::chooseDir);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::chooseFile);
    connect(saveAsAction,  &QAction::triggered, this, &MainWindow::saveFileAs);
    // connect()
    if (!currentFile.isEmpty()) {
    connect(saveAction,  &QAction::triggered, [this]() {
        Files[currentFile]->saveFile(ui->TextEditor->toPlainText());});
    }
    else {
        connect(saveAction,  &QAction::triggered, [this]() {
            QMessageBox::critical(this, "", "Choose file before saving");});
    }

    menu->addAction(openDirAction);
    menu->addAction(openFileAction);
    menu->addAction(saveAction);
    menu->addAction(saveAsAction);
    ui->actionLogo->setMenu(menu);
    menu->popup(QCursor::pos());
}

//ЕНТО Я СДЕЛАЛЬ ВОТ ДА ВОТ ТАК ВОТ ДА ДА

void MainWindow::copyString() {
    qDebug() << "copy";
}

void MainWindow::cutString() {
    qDebug() << "cut";
}

void MainWindow::pasteString() {
    qDebug() << "paste";
}

//END
