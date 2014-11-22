#include "twitterwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include <QRegExp>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include "twitterhandler.h"
#include "o2/o2globals.h"
#include <QScriptEngine>

twitterWidget::twitterWidget(twitterHandler * th,QWidget *parent) :
    th(th),QWidget(parent)
{
    picDone = false;
    mediaDone = false;
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

void twitterWidget::fetchTweet()
{
    if (th->linked()){

        QRegExp rx("/twitter\\.com\\/(\\w*)\\/status\\/(\\d*)");
        QString tweetURL = urlBox->text();
        int pos = rx.indexIn(tweetURL);

        if (pos != -1) {
            label->setText("Fetching tweet");

            userName = rx.cap(1);
            tweetId = rx.cap(2);

            QString tweetUrl = "https://api.twitter.com/1.1/statuses/show.json?id=" + tweetId + "&include_entities=true";

            QNetworkRequest request;

            request.setUrl(QUrl(tweetUrl));

            QString authString = "Bearer " + th->getToken();
            request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER,authString.toUtf8());

            QNetworkReply *reply = manager->get(request);

            connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));


        } else {
            label->setText("<font color=red>Invalid Tweet URL</font>");
        }
    } else {
        th->link();
        label->setText("<font color=red>Getting Auth Token/Failed to get Auth Token</font>");
    }


}

void twitterWidget::replyFinished() {

    picDone = false;
    mediaDone = false;

    urlArray.clear();
    mediaArray.clear();

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    QScriptValue value;
    QScriptEngine engine;

    value = engine.evaluate("(" + QString(replyData) + ")");

    QScriptValue urls = value.property("entities").property("urls");
    QScriptValue media = value.property("entities").property("media");

    tweetText = value.property("text").toString();
    twitterName = value.property("user").property("name").toString();
    tweetCreated = value.property("created_at").toString();
    profilePicUrl = value.property("user").property("profile_image_url").toString().replace("_normal","");

    int urlIterator = 0;

    while (urls.property(urlIterator).isValid()) {
        QMap<QString,QString> urlE;

        urlE["url"] = urls.property(urlIterator).property("url").toString();
        urlE["display_url"] = urls.property(urlIterator).property("display_url").toString();
        urlE["expanded_url"] = urls.property(urlIterator).property("expanded_url").toString();

        urlArray.insert(urlIterator,urlE);

        urlIterator++;
    }

    int mediaIterator = 0;
    mediaDone = true;
    while (media.property(mediaIterator).isValid()) {
        QMap<QString,QString> mediaE;

        mediaE["url"] = media.property(mediaIterator).property("url").toString();
        mediaE["display_url"] = media.property(mediaIterator).property("display_url").toString();
        mediaE["expanded_url"] = media.property(mediaIterator).property("expanded_url").toString();
        mediaE["type"] = media.property(mediaIterator).property("type").toString();
        mediaE["media_url"] = media.property(mediaIterator).property("media_url").toString();

        if(mediaIterator == 0 && mediaE["type"] == "photo") {
            mediaDone = false;
            QUrl mediaUrl(mediaE["media_url"]);
            QFileInfo mediaInfo(mediaUrl.path());
            mediaE["filename"] = mediaInfo.fileName();

            QString mediaOutFile = profilePicPath + "media/" +mediaE["filename"];
            qDebug() << mediaOutFile;
            QFile mediaFile(mediaOutFile);

            if (!mediaFile.exists()) {

                QNetworkReply *mediaReply = mediaManager->get(QNetworkRequest(QUrl(mediaE["media_url"])));

                connect(mediaReply, SIGNAL(finished()), this, SLOT(mediaFinished()));


            } else {
                mediaDone = true;
                //label->setText("<font color=green>Ok</font>");
            }
        } else {
            mediaDone = true;
        }

        mediaArray.insert(mediaIterator,mediaE);

        mediaIterator++;
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

void twitterWidget::picFinished() {

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    QUrl picUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    QString profilePicFilename = fileInfo.fileName();
    QString outFile = profilePicPath + profilePicFilename;

    QFile* file = new QFile;
    file->setFileName(outFile);
    file->open(QIODevice::WriteOnly);
    file->write(replyData);
    file->close();

    picDone = true;

    if (picDone && mediaDone) {
        label->setText("<font color=green>Ok</font>");
    }

    reply->deleteLater();

}

void twitterWidget::mediaFinished() {

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    /*QUrl mediaUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    QString profilePicFilename = fileInfo.fileName();*/
    QString outFile = profilePicPath + + "media/" + mediaArray[0]["filename"];
qDebug() << outFile;
    QFile* file = new QFile;
    file->setFileName(outFile);
    file->open(QIODevice::WriteOnly);
    file->write(replyData);
    file->close();

    mediaDone = true;

    if (picDone && mediaDone) {
        label->setText("<font color=green>Ok</font>");
    }

    reply->deleteLater();

}

void twitterWidget::setPath(QString path) {

    profilePicPath = path;

}

QString twitterWidget::getDate() {

    return tweetCreated;

}

QString twitterWidget::getProfilePicFilename() {

    return profilePicFilename;

}

QString twitterWidget::getProfilePicPath() {

    return profilePicPath + profilePicFilename;

}

QString twitterWidget::getTweetText() {

    return tweetText;

}

QString twitterWidget::getTwitterName() {

    return twitterName;

}

QString twitterWidget::getUsername() {

    return userName;

}

QVector<QMap<QString,QString> > twitterWidget::getURLs() {

    return urlArray;

}

QVector<QMap<QString,QString> > twitterWidget::getMedia() {

    return mediaArray;

}
