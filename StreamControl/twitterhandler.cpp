#include "twitterhandler.h"
#include "twitterOauth.h"
#include "o2twitter.h"
#include "o2/o2globals.h"

twitterHandler::twitterHandler(QObject *parent) :
    QObject(parent)
{
    o2 = new O2Twitter(this);
    o2->setClientId(OAUTH_KEY);
    o2->setClientSecret(OAUTH_SECRET);

}

QString twitterHandler::getToken() {
    return o2->token();
}

bool twitterHandler::linked() {
    return o2->linked();
}

void twitterHandler::link() {
    o2->link();
}
