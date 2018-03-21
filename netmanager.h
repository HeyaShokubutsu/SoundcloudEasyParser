#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSsl>
#include <QSslSocket>
#include <QUrl>
#include <QString>
#include <QFile>
#include <QEventLoop>
#include <QRegularExpression>

class NetManager : QObject
{
    Q_OBJECT
public:
    QByteArray gotData;
    explicit NetManager(QObject *parent = 0);
    ~NetManager();
    QByteArray getData(QUrl url);
    void setRequest(QUrl url);
    void parseSource(QString path);
    void parseMusic(QRegularExpressionMatch expression, QString path);
signals:
    void dataReady();
private slots:
    void replyFinished(QNetworkReply *re);
private:
    QEventLoop dataLoop;
    QNetworkAccessManager *manager;
    QNetworkReply *reply = NULL;
    QNetworkRequest *request;
};

#endif // NETMANAGER_H

