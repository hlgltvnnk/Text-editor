#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#endif // TEXTEDIT_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QVector>
#include <QStringList>
#include <QDir>
#include <QTableWidget>
#include <QApplication>
#include <QAbstractTableModel>
#include <QFileDialog>
#include <QtWidgets>
#include <QTextDocument>

namespace Ui {
class MainWindow;
}

    class TextEdit : public QObject {

    public:
        TextEdit(QString path);
        ~TextEdit();
        QString filename;
        QString buf;
        QTextDocument text;

        void setText(QString path);
        void changeText(QString info);
        void saveFile(QString info);
    };
