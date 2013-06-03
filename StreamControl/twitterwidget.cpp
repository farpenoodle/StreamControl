#include "twitterwidget.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include <QRegExp>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

twitterWidget::twitterWidget(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout;
    urlBox = new QLineEdit();
    label = new QLabel();
    fetchButton = new QPushButton();
    fetchButton->setText("Fetch");
    label->setText("Input tweet URL");
    layout->addWidget(urlBox,0,0);
    layout->addWidget(fetchButton,0,1);
    layout->addWidget(label,1,0,1,2);
    urlBox->setText("https://twitter.com/Kageshibari/status/341544211755196417");

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

        QString searchUrl = "http://search.twitter.com/search.json?q=from:" + userName;
        qDebug() << searchUrl;
        manager = new QNetworkAccessManager(this);
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
        profilePicUrl = tweetObject.find("profile_image_url").value().toString();
        qDebug() << userName + twitterName + tweetText + tweetCreated + profilePicUrl;

        label->setText("<font color=green>OK</font>");
    } else {
        label->setText("<font color=red>Tweet Not Found</font>");
    }
    reply->deleteLater();
}
