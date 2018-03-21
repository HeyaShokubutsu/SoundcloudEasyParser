#include "netmanager.h"

NetManager::NetManager(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    request(new QNetworkRequest)
{
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request->setSslConfiguration(config);

    connect(manager, SIGNAL(finished(QNetworkReply* )), this,
                     SLOT(replyFinished(QNetworkReply* )));

    connect(this, SIGNAL(dataReady()), &dataLoop,
            SLOT(quit()));
}

NetManager::~NetManager()
{
    delete manager;
    delete request;
}

QByteArray NetManager::getData(QUrl url)
{
    request->setUrl(url);
    reply = manager->get(*request);
    dataLoop.exec();
    return gotData;
}

void NetManager::replyFinished(QNetworkReply *re)
{
   qDebug() << re->error();
   gotData = re->readAll();
   emit dataReady();
}

void NetManager::parseSource(QString path)
{
    QRegularExpression trackTemplate("(<li><h2><a href=\")(/[\\w|\\-|\\d|\/]+)(\">)([^<]+)(</a><\/h2><\/li>)");
    QRegularExpressionMatchIterator matchIterator = trackTemplate.globalMatch(QString::fromUtf8(gotData));
    while(matchIterator.hasNext())
    {
        parseMusic(matchIterator.next(), path);
    }
    qDebug() << "Source captured succesfully!";
}
void NetManager::parseMusic(QRegularExpressionMatch expression, QString path)
{
    QRegularExpression trackIdtemplate("(content=\"soundcloud://sounds:)(\\d\\d\\d\\d\\d\\d\\d\\d\\d)");
    QRegularExpression directIdtemplate("(\"location\":\")([^\"]+)");
    QFile out(path + "/" + expression.captured(4) + ".mp3");
    getData(QUrl("https://soundcloud.com" + expression.captured(2)));
    QRegularExpressionMatch trackId = trackIdtemplate.match(QString::fromUtf8(gotData));
    getData(QUrl("https://api.soundcloud.com/tracks/" + trackId.captured(2)+ "/stream?client_id=3GtnQtvbxU1K5jhCPJcq2xyZ6xtctDIc"));
    QRegularExpressionMatch directId = directIdtemplate.match(QString::fromUtf8(gotData));
    out.open(QIODevice::WriteOnly);
    out.write(getData(QUrl(directId.captured(2))));
    out.close();
}
