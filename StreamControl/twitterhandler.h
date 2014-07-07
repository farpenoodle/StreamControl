#ifndef TWITTERHANDLER_H
#define TWITTERHANDLER_H
#include "o2twitter.h"

#include <QObject>
#include <QString>

class twitterHandler : public QObject
{
    Q_OBJECT
public:
    explicit twitterHandler(QObject *parent = 0);

signals:

public slots:
    QString getToken();
    bool linked();
    void link();

private:
    O2Twitter *o2;

};

#endif // TWITTERHANDLER_H
