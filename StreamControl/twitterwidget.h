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
#include <QVector>

#include "twitterHandler.h"


class twitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit twitterWidget(twitterHandler *th, QWidget *parent = 0);

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
    bool            picDone;
    bool            mediaDone;
    QVector<QMap<QString,QString> > urlArray;
    QVector<QMap<QString,QString> > mediaArray;

    QNetworkAccessManager   *manager;
    QNetworkAccessManager   *picManager;
    QNetworkAccessManager   *mediaManager;

    twitterHandler *th;

    
signals:
    
public slots:
    void fetchTweet();
    void replyFinished();
    void picFinished();
    void mediaFinished();
    void setPath(QString);

    QString getUsername();
    QString getTwitterName();
    QString getTweetText();
    QString getProfilePicFilename();
    QString getProfilePicPath();
    QString getDate();
    QVector<QMap<QString,QString> > getURLs();
    QVector<QMap<QString,QString> > getMedia();

};

#endif // TWITTER_H
