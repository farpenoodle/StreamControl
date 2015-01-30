#ifndef TWITTERHANDLER_H
#define TWITTERHANDLER_H

#include <QObject>
#include <QString>

class O2Twitter;

class TwitterHandler : public QObject
{
    Q_OBJECT
public:
    explicit TwitterHandler(QObject *parent = 0);

signals:

public slots:
    QString getToken();
    bool linked();
    void link();

private:
    O2Twitter *o2;

};

#endif // TWITTERHANDLER_H
