#include "twitterwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include <QRegularExpression>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDateTime>
#include <QLocale>
#include <QtMath>
#include <cmath>

// Token the syndication endpoint expects: ((id / 1e15) * pi).toString(36) with
// zeros and the radix point stripped. Mirrors V8's DoubleToRadixCString so the
// result matches what twitter's embed JS sends.
static QString syndicationToken(const QString &id)
{
    const char chars[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    const int radix = 36;

    double value = id.toDouble() / 1e15 * M_PI;
    double integer = std::floor(value);
    double fraction = value - integer;
    double delta = 0.5 * (std::nextafter(value, INFINITY) - value);
    delta = std::max(std::nextafter(0.0, 1.0), delta);

    QString fractionDigits;
    if (fraction >= delta) {
        do {
            fraction *= radix;
            delta *= radix;
            int digit = static_cast<int>(fraction);
            fractionDigits += chars[digit];
            fraction -= digit;
            if (fraction > 0.5 || (fraction == 0.5 && (digit & 1))) {
                if (fraction + delta > 1) {
                    // round up, propagating carries back through the digits
                    while (true) {
                        if (fractionDigits.isEmpty()) {
                            integer += 1;
                            break;
                        }
                        QChar c = fractionDigits.back();
                        fractionDigits.chop(1);
                        int d = c > '9' ? (c.toLatin1() - 'a' + 10) : (c.toLatin1() - '0');
                        if (d + 1 < radix) {
                            fractionDigits += chars[d + 1];
                            break;
                        }
                    }
                    break;
                }
            }
        } while (fraction >= delta);
    }

    QString integerDigits;
    do {
        double rem = std::fmod(integer, radix);
        integerDigits.prepend(chars[static_cast<int>(rem)]);
        integer = (integer - rem) / radix;
    } while (integer > 0);

    QString token = integerDigits + fractionDigits;
    return token.remove('0');
}

TwitterWidget::TwitterWidget(QWidget *parent) :
    QWidget(parent)
{
    picDone = false;
    mediaDone = false;
    embedJSON = false;
    layout = new QGridLayout;
    urlBox = new QLineEdit();
    label = new QLabel();
    fetchButton = new QPushButton();
    fetchButton->setText("Fetch Tweet");
    label->setText("Input tweet URL");
    layout->addWidget(urlBox,0,0);
    layout->addWidget(fetchButton,0,1);
    layout->addWidget(label,1,0,1,2);
    manager = new QNetworkAccessManager;
    picManager = new QNetworkAccessManager;
    mediaManager = new QNetworkAccessManager;

    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetchTweet()));

    this->setLayout(layout);

}

void TwitterWidget::fetchTweet()
{
    QRegularExpression rx("(?:^|[/.])(?:twitter|x)\\.com\\/(\\w+)\\/status(?:es)?\\/(\\d+)");
    QString tweetURL = urlBox->text();
    QRegularExpressionMatch rxmatch = rx.match(tweetURL);

    if (rxmatch.hasMatch()) {
        label->setText("Fetching tweet");

        userName = rxmatch.captured(1);
        tweetId = rxmatch.captured(2);

        QString tweetUrl = "https://cdn.syndication.twimg.com/tweet-result?id=" + tweetId + "&token=" + syndicationToken(tweetId) + "&lang=en";

        QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(tweetUrl)));

        connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));

    } else {
        label->setText("<font color=red>Invalid Tweet URL</font>");
    }

}

void TwitterWidget::replyFinished() {

    picDone = false;
    // only cleared while a media download is pending; text-only tweets have nothing to wait for
    mediaDone = true;

    urlArray.clear();
    mediaArray.clear();

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    //qDebug() << QString(replyData);

    QJsonDocument jsonDoc;
    jsonDoc = QJsonDocument::fromJson(QString(replyData).toUtf8());

    QJsonObject jsonObj;
    jsonObj = jsonDoc.object();

    // deleted/protected/nonexistent tweets come back as an error or an empty object
    if (reply->error() != QNetworkReply::NoError || !jsonObj.contains("id_str")) {
        label->setText("<font color=red>Tweet not found or unavailable</font>");
        reply->deleteLater();
        return;
    }

    tweetJSON = jsonObj;

    QJsonObject entities = jsonObj["entities"].toObject();
    QJsonObject user = jsonObj["user"].toObject();

    QJsonArray urls = entities["urls"].toArray();
    QJsonArray media = jsonObj["mediaDetails"].toArray();

    tweetText = jsonObj["text"].toString();
    twitterName = user["name"].toString();
    if (user.contains("screen_name")) {
        userName = user["screen_name"].toString();
    }
    // syndication returns ISO 8601; keep the old v1.1 format so existing layouts still parse it
    QDateTime created = QDateTime::fromString(jsonObj["created_at"].toString(), Qt::ISODateWithMs);
    if (created.isValid()) {
        tweetCreated = QLocale::c().toString(created.toUTC(), "ddd MMM dd HH:mm:ss +0000 yyyy");
    } else {
        tweetCreated = jsonObj["created_at"].toString();
    }
    profilePicUrl = user["profile_image_url_https"].toString().replace("_normal","");

    int urli;
    for (urli = 0; urli != urls.count(); urli++) {
        QMap<QString,QString> urlE;
        QJsonObject urliE = urls.at(urli).toObject();
        urlE["url"] = urliE["url"].toString();
        urlE["display_url"] = urliE["display_url"].toString();
        urlE["expanded_url"] = urliE["expanded_url"].toString();

        urlArray.insert(urli,urlE);
    }

    int mediai;
    for (mediai = 0; mediai != media.count(); mediai++) {
        QMap<QString,QString> mediaE;
        QJsonObject mediaiE = media.at(mediai).toObject();

        mediaE["url"] = mediaiE["url"].toString();
        mediaE["display_url"] = mediaiE["display_url"].toString();
        mediaE["expanded_url"] = mediaiE["expanded_url"].toString();
        mediaE["type"] = mediaiE["type"].toString();
        mediaE["media_url"] = mediaiE["media_url_https"].toString();

        if(mediai == 0 && mediaE["type"] == "photo") {
            QUrl mediaUrl(mediaE["media_url"]);
            QFileInfo mediaInfo(mediaUrl.path());
            mediaE["filename"] = mediaInfo.fileName();

            QString mediaOutFile = profilePicPath + "media/" +mediaE["filename"];
            qDebug() << mediaOutFile;
            qDebug() << mediaE["media_url"];
            QFile mediaFile(mediaOutFile);

            if (!mediaFile.exists()) {
                mediaDone = false;

                QNetworkReply *mediaReply = mediaManager->get(QNetworkRequest(QUrl(mediaE["media_url"])));

                connect(mediaReply, SIGNAL(finished()), this, SLOT(mediaFinished()));

            }
        }

        mediaArray.insert(mediai,mediaE);
    }


    //qDebug() << tweetText;

    QUrl picUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    profilePicFilename = fileInfo.fileName();
    QString outFile = profilePicPath + profilePicFilename;
    QFile file(outFile);


    if (!file.exists()) {

        QNetworkReply *picReply = picManager->get(QNetworkRequest(QUrl(profilePicUrl)));

        connect(picReply, SIGNAL(finished()), this, SLOT(picFinished()));


    } else {
        picDone = true;
        //label->setText("<font color=green>Ok</font>");
    }


    if (picDone && mediaDone) {
        label->setText("<font color=green>Ok</font>");
    }

    reply->deleteLater();
}

void TwitterWidget::picFinished() {

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    QUrl picUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    QString profilePicFilename = fileInfo.fileName();
    QString outFile = profilePicPath + profilePicFilename;

    QFile* file = new QFile;
    file->setFileName(outFile);
    file->open(QIODevice::ReadWrite);
    file->write(replyData);
    file->close();

    picDone = true;

    if (picDone && mediaDone) {
        label->setText("<font color=green>Ok</font>");
    }

    reply->deleteLater();

}

void TwitterWidget::mediaFinished() {

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    /*QUrl mediaUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    QString profilePicFilename = fileInfo.fileName();*/
    QString outFile = profilePicPath + "media/" + mediaArray[0]["filename"];

qDebug() << outFile;
    QFile* file = new QFile;
    file->setFileName(outFile);
    file->open(QIODevice::ReadWrite);
    file->write(replyData);
    file->close();

    mediaDone = true;

    if (picDone && mediaDone) {
        label->setText("<font color=green>Ok</font>");
    }

    reply->deleteLater();

}

void TwitterWidget::setPath(QString path) {

    profilePicPath = path;

}
void TwitterWidget::setEmbed(bool embed) {

    embedJSON = embed;

}

QString TwitterWidget::getDate() {

    return tweetCreated;

}

QString TwitterWidget::getProfilePicFilename() {

    return profilePicFilename;

}

QString TwitterWidget::getProfilePicPath() {

    return profilePicPath + profilePicFilename;

}

QString TwitterWidget::getTweetText() {

    return tweetText;

}

QString TwitterWidget::getTwitterName() {

    return twitterName;

}

QString TwitterWidget::getUsername() {

    return userName;

}

QJsonValue TwitterWidget::getJSON() {

    return tweetJSON;
}

QVector<QMap<QString,QString> > TwitterWidget::getURLs() {

    return urlArray;

}

QVector<QMap<QString,QString> > TwitterWidget::getMedia() {

    return mediaArray;

}

bool TwitterWidget::isEmbed() {
    return embedJSON;
}
