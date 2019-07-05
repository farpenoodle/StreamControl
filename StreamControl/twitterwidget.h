#ifndef TWITTERWIDGET_H
#define TWITTERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QJsonDocument>
#include <QJsonValue>

class TwitterHandler;
class QNetworkAccessManager;
class QLineEdit;
class QLabel;
class QGridLayout;
class QPushButton;

class TwitterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TwitterWidget(TwitterHandler *th, QWidget *parent = 0);

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
    QJsonValue     tweetJSON;
    bool            picDone;
    bool            mediaDone;
    bool            embedJSON;
    QVector<QMap<QString,QString> > urlArray;
    QVector<QMap<QString,QString> > mediaArray;

    QNetworkAccessManager   *manager;
    QNetworkAccessManager   *picManager;
    QNetworkAccessManager   *mediaManager;

    TwitterHandler *th;

signals:

public slots:
    void fetchTweet();
    void replyFinished();
    void picFinished();
    void mediaFinished();
    void setPath(QString);
    void setEmbed(bool);

    QString getUsername();
    QString getTwitterName();
    QString getTweetText();
    QString getProfilePicFilename();
    QString getProfilePicPath();
    QString getDate();
    QJsonValue getJSON();
    bool isEmbed();
    QVector<QMap<QString,QString> > getURLs();
    QVector<QMap<QString,QString> > getMedia();

};


#endif // TWITTERWIDGET_H
