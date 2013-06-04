#include "twitterwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QUrl>
#include <QFileInfo>
#include <QFile>

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

    connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetchTweet()));

    this->setLayout(layout);
}

void twitterWidget::fetchTweet()
{
    QRegExp rx("/twitter\\.com\\/(\\w*)\\/status\\/(\\d*)");
    QString tweetURL = urlBox->text();
    int pos = rx.indexIn(tweetURL);

    if (pos != -1) {
        label->setText("Fetching tweet");

        userName = rx.cap(1);
        tweetId = rx.cap(2);

        QString searchUrl = "http://search.twitter.com/search.json?q=from:" + userName + "&since_id=" + QString::number(tweetId.toULongLong() - 1) + "&max_id=" + tweetId;

        manager = new QNetworkAccessManager;
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

        manager->get(QNetworkRequest(QUrl(searchUrl)));


    } else {
        label->setText("<font color=red>Invalid Tweet URL</font>");
    }



}

void twitterWidget::replyFinished(QNetworkReply *reply) {
    QJsonDocument tweetsJson = QJsonDocument::fromJson(reply->readAll());
    QJsonArray tweetArray = tweetsJson.object().find("results").value().toArray();

    bool found = false;

    QJsonObject tweetObject;

    int tweetNum = tweetArray.count();

    for (int i = 0; i < tweetNum;i++) {
        tweetObject = tweetArray.at(i).toObject();
        if (tweetObject.find("id_str").value().toString() == tweetId) {
            found = true;
            break;
        }
    }

    if (found == true) {
        twitterName = tweetObject.find("from_user_name").value().toString();
        tweetText = tweetObject.find("text").value().toString();
        tweetCreated = tweetObject.find("created_at").value().toString();
        profilePicUrl = tweetObject.find("profile_image_url").value().toString().replace("_normal","");

        QUrl picUrl(profilePicUrl);
        QFileInfo fileInfo(picUrl.path());

        profilePicFilename = fileInfo.fileName();
        QString outFile = profilePicPath + profilePicFilename;
        QFile file(outFile);

        if (!file.exists()) {
            picManager = new QNetworkAccessManager;
            connect(picManager, SIGNAL(finished(QNetworkReply*)),
                    this, SLOT(picFinished(QNetworkReply*)));

            picManager->get(QNetworkRequest(QUrl(profilePicUrl)));
        } else {
            label->setText("<font color=green>Ok</font>");
        }
    } else {
        label->setText("<font color=red>Tweet Not Found</font>");
    }
    reply->deleteLater();
}

void twitterWidget::picFinished(QNetworkReply *reply) {

    QUrl picUrl(profilePicUrl);
    QFileInfo fileInfo(picUrl.path());

    QString profilePicFilename = fileInfo.fileName();
    QString outFile = profilePicPath + profilePicFilename;

    QFile* file = new QFile;
    file->setFileName(outFile);
    file->open(QIODevice::WriteOnly);
    file->write(reply->readAll());
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
