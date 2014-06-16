#include "twitterwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include <QRegExp>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include "twitterOauth.h"
#include "o2twitter.h"
#include "o2/o2globals.h"
#include <QScriptEngine>

twitterWidget::twitterWidget(QWidget *parent) :
    QWidget(parent)
{
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

    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetchTweet()));

    this->setLayout(layout);

    o2 = new O2Twitter(this);
    o2->setClientId(OAUTH_KEY);
    o2->setClientSecret(OAUTH_SECRET);

    connect(o2, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(o2, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
    connect(o2, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
}

void twitterWidget::fetchTweet()
{

    if (o2->linked()){

        QRegExp rx("/twitter\\.com\\/(\\w*)\\/status\\/(\\d*)");
        QString tweetURL = urlBox->text();
        int pos = rx.indexIn(tweetURL);

        if (pos != -1) {
            label->setText("Fetching tweet");

            userName = rx.cap(1);
            tweetId = rx.cap(2);

            QString tweetUrl = "https://api.twitter.com/1.1/statuses/show.json?id=" + tweetId;

            QNetworkRequest request;

            request.setUrl(QUrl(tweetUrl));

            QString authString = "Bearer " + o2->token();
            request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER,authString.toUtf8());

            QNetworkReply *reply = manager->get(request);

            connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));


        } else {
            label->setText("<font color=red>Invalid Tweet URL</font>");
        }
    } else {
        label->setText("<font color=red>Getting Auth Token</font>");
        o2->link();
    }


}

void twitterWidget::replyFinished() {

    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    QByteArray replyData = reply->readAll();

    QScriptValue value;
    QScriptEngine engine;

    value = engine.evaluate("(" + QString(replyData) + ")");

    QScriptValue urls = value.property("entities").property("urls");

    tweetText = value.property("text").toString();
    twitterName = value.property("user").property("name").toString();
    tweetCreated = value.property("created_at").toString();
    profilePicUrl = value.property("user").property("profile_image_url").toString().replace("_normal","");

    int urlIterator = 0;

    while (urls.property(urlIterator).isValid()) {
        tweetText = tweetText.replace(urls.property(urlIterator).property("url").toString(),urls.property(urlIterator).property("expanded_url").toString());
        urlIterator++;
    }

    QUrl picUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    profilePicFilename = fileInfo.fileName();
    QString outFile = profilePicPath + profilePicFilename;
    QFile file(outFile);

    if (!file.exists()) {

        QNetworkReply *picReply = picManager->get(QNetworkRequest(QUrl(profilePicUrl)));

        connect(picReply, SIGNAL(finished()), this, SLOT(picFinished()));


    } else {
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

    label->setText("<font color=green>Ok</font>");

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


//OAuth Stuff
void twitterWidget::onLinkedChanged() {
    // Linking (login) state has changed.
    // Use o1->linked() to get the actual state
}

void twitterWidget::onLinkingFailed() {
    // Login has failed
    label->setText("<font color=red>Failed to get Auth Token</font>");
}

void twitterWidget::onLinkingSucceeded() {
    label->setText("<font color=green>Auth Token granted!</font>");

}

