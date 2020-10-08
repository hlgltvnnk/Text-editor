#include "textedit.h"


TextEdit::TextEdit(QString path) : filename(path){
    setText(path);
}

TextEdit::~TextEdit() {
}

void TextEdit::setText(QString path) {
    QFile file(path);
    QString line;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd())
            line.append(stream.readLine()+"\n");
        text.setPlainText(line);
    }
    file.close();
}

void TextEdit::changeText(QString info) {
    text.setPlainText(info);
}

void TextEdit::saveFile(QString info) {
    std::cout<< filename.toLocal8Bit().data() <<std::endl;
    changeText(info);
    QFile file(filename);
    file.open(QIODevice::ReadWrite);
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_5);
    out<< text.toPlainText().toLocal8Bit().data();
    file.close();
}
