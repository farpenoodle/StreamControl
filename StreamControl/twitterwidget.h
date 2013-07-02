#ifndef TWITTERWIDGET_H
#define TWITTERWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

#include "o2twitter.h"


class twitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit twitterWidget(QWidget *parent = 0);

private:
    QGridLayout     *layout;
    QLineEdit       *urlBox;
    QLabel          *label;
    QPushButton     *fetchButton;
    QString         userName;
    QString         tweetText;
    QString         twitterName;
    QString         tweetId;
    QString         tweetCreated;
    QString         profilePicPath;
    QString         profilePicFilename;
    QString         profilePicUrl;

    QNetworkAccessManager   *manager;
    QNetworkAccessManager   *picManager;

    O2Twitter *o2;

    
signals:
    
public slots:
    void fetchTweet();
    void replyFinished();
    void picFinished();
    void setPath(QString);

    void onLinkedChanged();
    void onLinkingFailed();
    void onLinkingSucceeded();

    QString getUsername();
    QString getTwitterName();
    QString getTweetText();
    QString getProfilePicFilename();
    QString getProfilePicPath();
    QString getDate();

};

#endif // TWITTER_H
