#include "twitterhandler.h"
#include "twitterOauth.h"
#include "o2twitter.h"
#include "o2/o2globals.h"

TwitterHandler::TwitterHandler(QObject *parent) :
    QObject(parent)
{
    o2 = new O2Twitter(this);
    o2->setClientId(OAUTH_KEY);
    o2->setClientSecret(OAUTH_SECRET);

}

QString TwitterHandler::getToken() {
    return o2->token();
}

bool TwitterHandler::linked() {
    return o2->linked();
}

void TwitterHandler::link() {
    o2->link();
}
