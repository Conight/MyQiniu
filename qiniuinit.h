#ifndef QINIUINIT_H
#define QINIUINIT_H

#include "sdk/qiniu/io.h"
#include "sdk/qiniu/resumable_io.h"
#include "sdk/qiniu/rs.h"
#include "sdk/qiniu/base.h"

#include <QDebug>

void gQiniuDebug(Qiniu_Client* client, Qiniu_Error error) {
    qDebug() << QString("\nerror clde: %1, message: %2\n")
                .arg(error.code).arg(error.message);
    qDebug() << QString("respose header:\n%1")
                .arg(Qiniu_Buffer_CStr(&client->respHeader));
    qDebug() << QString("respose body:\n%1")
                .arg(Qiniu_Buffer_CStr(&client->b));
}

/*得到上传文件的token*/
char* gQiniuUploadToken(const char* bucket, Qiniu_Mac* mac)
{
    Qiniu_RS_PutPolicy putPolicy;
    Qiniu_Zero(putPolicy);
    putPolicy.scope = bucket;
    qDebug() << "gQiniuUploadToken: " << Qiniu_RS_PutPolicy_Token(&putPolicy, mac);
    return Qiniu_RS_PutPolicy_Token(&putPolicy, mac);
}

/*得到下载文件的url的token*/
char* gQiniuDownloadUrl(const char* domain, const char* key, Qiniu_Mac* mac)
{

    char* url = 0;
    char* baseUrl = 0;

    Qiniu_RS_GetPolicy getPolicy;
    Qiniu_Zero(getPolicy);

    baseUrl = Qiniu_RS_MakeBaseUrl(domain, key);
    url = Qiniu_RS_GetPolicy_MakeRequest(&getPolicy, baseUrl, mac);
    Qiniu_Free(baseUrl);
    return url;
}

void gQiniuGetFileStat(Qiniu_Client* pClient,
                     const char* bucketName,
                     const char* keyName)
{
    Qiniu_RS_StatRet statRet;
    Qiniu_Error error = Qiniu_RS_Stat(pClient,
                                      &statRet,
                                      bucketName,
                                      keyName);
    /* 判断http返回值*/
    if (error.code != 200)
    {   /*非200，不正确返回*/
        qDebug() << QString("get file %1:%2 stat error.\n")
                    .arg(bucketName).arg(keyName);
        gQiniuDebug(pClient, error);
    }else
    {
         qDebug() << QString("get file %1:%2 stat success.\n")
                     .arg(bucketName)
                     .arg(keyName);
    }
}

void gQiniuUploadFile(Qiniu_Client* pClient,
                      const char* bucketName,
                      Qiniu_Mac* mac,
                      const char* fileName,
                      const char* uploadFileName)
{
    const char* uploadName = uploadFileName;
    /*得到uploadKey*/
    const char* uploadtoken = gQiniuUploadToken(bucketName, mac);

    const char* pLocalFilePath = fileName;

    Qiniu_Io_PutRet putRet;
    Qiniu_Error error = Qiniu_Io_PutFile(pClient, &putRet,
                                         uploadtoken, uploadName,
                                         pLocalFilePath, NULL);
    if (error.code != 200)
    {
        qDebug() << QString("Upload File %1 To %2:%3 error.\n")
                    .arg(pLocalFilePath)
                    .arg(bucketName)
                    .arg(uploadName);
        gQiniuDebug(pClient, error);
    }
    else
    {
        qDebug() << QString("Upload File %1 To %2:%3 success.\n")
                    .arg(pLocalFilePath)
                    .arg(bucketName)
                    .arg(uploadName);
    }

    Qiniu_Free((char*)uploadtoken);
}


void gQiniuGetDownloadURL(const char* bucketName, Qiniu_Mac* mac)
{

    char* domain = Qiniu_String_Concat2(bucketName, "o8t8tisr0.bkt.clouddn.com");
    const char* downloadName = "cat.jpg";
    char* pUrl = gQiniuDownloadUrl(domain, downloadName, mac);

    if (0 == pUrl)
    {
        qDebug() << QString("get URL %1:%2 error.\n")
                    .arg(bucketName).arg(downloadName);
    }
    else
    {
        qDebug() << QString("get URL %1:%2 is %3.\n")
                    .arg(bucketName)
                    .arg(downloadName)
                    .arg(pUrl);
    }

    Qiniu_Free(pUrl);
    Qiniu_Free(domain);
}

void gQiniuConnectInit() {
//    Qiniu_Client client;
//    Qiniu_Mac    mac;
//    char* bucketName = (char*)"apitest";

//    mac.accessKey ="aof6uBwzGVSQbjSd8aGjYkhaIwFckLGAvihs3Ruu";
//    mac.secretKey = "Sexs-tBxTpeldkXFyH3vCIcn3dB_L821ddE3eGAy";

//    Qiniu_Servend_Init(-1);
//    Qiniu_Client_InitMacAuth(&client, 1024, &mac);
//    gQiniuUploadFile(&client, bucketName, &mac);
    //gQiniuGetFileStat(&client, bucketName, "cat.jpg");
    //gQiniuMoveFile(&client, bucketName, "cat.jpg", "cat22.jpg");
    //gQiniuDeleteFile(&client, bucketName, "cat.jpg");
    //gQiniuGetDownloadURL(bucketName, &mac);

//    Qiniu_Client_Cleanup(&client);
//    Qiniu_Servend_Cleanup();
}

#endif // QINIUINIT_H
