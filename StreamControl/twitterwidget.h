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
    QString         profilePicUrl;

    QNetworkAccessManager   *manager;
    QNetworkAccessManager   *picManager;

    
signals:
    
public slots:
    void fetchTweet();
    void replyFinished(QNetworkReply *reply);

};

#endif // TWITTER_H
