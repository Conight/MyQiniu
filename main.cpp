#include "myqiniu.h"
#include "configfile.h"
#include <QApplication>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    if (isRight() == true) {
        qDebug() << isRight();
    } else {
        qDebug() << isRight();
        setDialog d;
        d.exec();
    }

    MyQiniu w;
    w.show();

    return a.exec();
}
