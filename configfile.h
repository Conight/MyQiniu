#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QFileInfo>
#include <QSettings>
#include <QProcessEnvironment>
#include <QDebug>

struct Qiniu {
    QString bucket;
    QString url;
    QString accessKey;
    QString secretKey;
};

static bool isRight() {
    QSettings qiniuConf("conight", "MyQiniuConf");

    qiniuConf.beginGroup("QiniuKey");

    if (!qiniuConf.value("bucket").toString().isEmpty() &&
            !qiniuConf.value("url").toString().isEmpty() &&
            !qiniuConf.value("accessKey").toString().isEmpty() &&
            !qiniuConf.value("secretKey").toString().isEmpty()) {
        qiniuConf.endGroup();
        return true;
    } else {
        qiniuConf.endGroup();
        return false;
    }
}

#endif // CONFIGFILE_H
