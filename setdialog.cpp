#include "setdialog.h"
#include "ui_setdialog.h"
#include "configfile.h"
#include "myqiniu.h"

#include <QSettings>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

setDialog::setDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setDialog)
{
    ui->setupUi(this);
    setWindowTitle("Setting");
    setQiniuKey();
}

setDialog::~setDialog()
{
    delete ui;
}

void setDialog::setQiniuKey() {
    Qiniu qiniu;

    QSettings config("conight", "MyQiniuConf");
    config.beginGroup("QiniuKey");

    qiniu.bucket = config.value("bucket").toString();
    qiniu.url = config.value("url").toString();
    qiniu.accessKey = config.value("accessKey").toString();
    qiniu.secretKey = config.value("secretKey").toString();

    ui->bucketLineEdit->setText(qiniu.bucket);
    ui->urlLineEdit->setText(qiniu.url);
    ui->accessKeyLineEdit->setText(qiniu.accessKey);
    ui->secretKeyLineEdit->setText(qiniu.secretKey);

    config.endGroup();
}

void setDialog::on_okButton_clicked()
{
    if (ui->bucketLineEdit->text().isEmpty() ||
            ui->urlLineEdit->text().isEmpty() ||
            ui->accessKeyLineEdit->text().isEmpty() ||
            ui->secretKeyLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, tr("Wrong"),
                             tr("Please confirm your insert!"),
                             QMessageBox::Ok);
    } else {
        QSettings config("conight", "MyQiniuConf");
        config.beginGroup("QiniuKey");
        config.setValue("bucket", ui->bucketLineEdit->text());
        config.setValue("url", ui->urlLineEdit->text());
        config.setValue("accessKey", ui->accessKeyLineEdit->text());
        config.setValue("secretKey", ui->secretKeyLineEdit->text());
        config.endGroup();
        accept();
    }
}

void setDialog::on_cancelButton_clicked()
{
    reject();
}
