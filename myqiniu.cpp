#include "myqiniu.h"
#include "ui_myqiniu.h"
#include "qiniuinit.h"
#include "configfile.h"

#include <QSettings>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QClipboard>

MyQiniu::MyQiniu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyQiniu)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    setAcceptDrops(true);

    //creat config file(path:~/.config/conight/MyQiniuConf)
    QSettings readConf("conight", "MyQiniuConf");
    readConf.beginGroup("QiniuKey");
    qiniu.bucket = readConf.value("bucket").toString();
    qiniu.url = readConf.value("url").toString();
    qiniu.accessKey = readConf.value("accessKey").toString();
    qiniu.secretKey = readConf.value("secretKey").toString();
    readConf.endGroup();
}

MyQiniu::~MyQiniu()
{
    delete ui;
}

void MyQiniu::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list")) {
        event->acceptProposedAction();
    }
}

void MyQiniu::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //get file name
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        const char* fileMark = url.fileName().toStdString().c_str();

        ui->textEdit->append(file_name);

        //QString -> char*
        std::string str;
        str = file_name.toStdString();
        const char* fileName = str.c_str();

        std::string str1, str2, str3, str4;
        str1 = qiniu.bucket.toStdString();
        bucketName = str1.c_str();

        str2 = qiniu.accessKey.toStdString();
        mac.accessKey = str2.c_str();

        str3 = qiniu.secretKey.toStdString();
        mac.secretKey = str3.c_str();

        str4 = qiniu.url.toStdString();
        dom = str4.c_str();

        //init connect
        Qiniu_Servend_Init(-1);
        Qiniu_Client_InitMacAuth(&client, 1024, &mac);

        //upload file
        gQiniuUploadFile(&client, bucketName, &mac,
                         fileName, fileMark);

        //set clipboard
        board = QApplication::clipboard();
        board->setText(getFileUrl(qiniu.url,
                                  url.fileName()));

        //close connect
        Qiniu_Client_Cleanup(&client);
        Qiniu_Servend_Cleanup();
    }
}

QString MyQiniu::getFileUrl(QString url, QString filename) {
    return url.append("/").append(filename);
}

void MyQiniu::on_settingPushButton_clicked()
{
    setdialog.exec();
}

void MyQiniu::on_aboutPushButton_clicked()
{
    ui->textEdit->append(tr("Open Source \n"
                            "LICENSE & more\n"
                            "https://github.com/Conight/MyQiniu"));
}
