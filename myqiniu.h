#ifndef MYQINIU_H
#define MYQINIU_H

#include "setdialog.h"
#include "configfile.h"
#include "sdk/qiniu/io.h"
#include "sdk/qiniu/resumable_io.h"
#include "sdk/qiniu/rs.h"
#include "sdk/qiniu/base.h"

#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MyQiniu;
}

class MyQiniu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyQiniu(QWidget *parent = 0);
    ~MyQiniu();
    setDialog setdialog;
    Qiniu_Client client;
    Qiniu_Mac    mac;
    const char* bucketName;
    Qiniu qiniu;
    const char* dom;
    QString fileUrl;
    QClipboard *board;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_settingPushButton_clicked();

    void on_aboutPushButton_clicked();

private:
    Ui::MyQiniu *ui;
    QString getFileUrl(QString url, QString filename);
};

#endif // MYQINIU_H
