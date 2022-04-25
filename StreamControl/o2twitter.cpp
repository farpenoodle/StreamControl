#include <QDebug>
#include <QDateTime>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QDesktopServices>
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonObject>
#endif

#include "o2twitter.h"
#include "o2/o0globals.h"

O2Twitter::O2Twitter(QObject *parent): O2(parent) {
    setTokenUrl("https://api.twitter.com/oauth2/token");
}

void O2Twitter::link() {

    qDebug() << "O2::link";
    if (linked()) {
        qDebug() << "O2::link: Linked already";
        emit linkingSucceeded();
        return;
    }

    QString authString = clientId_ + ":" + clientSecret_;
    QString base64String = "Basic " + authString.toUtf8().toBase64();

    QNetworkRequest request(tokenUrl());

    request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER,base64String.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/x-www-form-urlencoded;charset=UTF-8").toUtf8());

    QNetworkReply *reply = manager_->post(request, QString("grant_type=client_credentials").toUtf8());

    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onTokenReplyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(onTokenReplyFinished()));

    // FIXME: Delete relevant cookies, too
}


void O2Twitter::onTokenReplyFinished() {
    qDebug() << "O2::onTokenReplyFinished";
    QNetworkReply *tokenReply = qobject_cast<QNetworkReply *>(sender());
    if (tokenReply->error() == QNetworkReply::NoError) {
        QByteArray replyData = tokenReply->readAll();
        //value = engine.evaluate("(" + QString(replyData) + ")");
        QJsonDocument jsonResponse = QJsonDocument::fromJson(QString(replyData).toUtf8());
        QJsonObject jsonObject = jsonResponse.object();
        QString twitterToken = jsonObject[O2_OAUTH2_ACCESS_TOKEN].toString();

        setToken(twitterToken);
        timedReplies_.remove(tokenReply);
        emit linkedChanged();
        emit tokenChanged();
        emit linkingSucceeded();
    }

    tokenReply->deleteLater();
}

void O2Twitter::onTokenReplyError(QNetworkReply::NetworkError error) {
    QNetworkReply *tokenReply = qobject_cast<QNetworkReply *>(sender());
    qDebug() << "O2::onTokenReplyError" << error << tokenReply->errorString();
    qDebug() << "" << tokenReply->readAll();
    setToken(QString());
    setRefreshToken(QString());
    timedReplies_.remove(tokenReply);
    emit linkedChanged();
    emit tokenChanged();
    emit linkingFailed();
}

QString O2Twitter::token() {
    return bearerToken;
}

void O2Twitter::setToken(const QString &v) {
    bearerToken = v;
}

bool O2Twitter::linked() {
    if (token().length() > 0) {
        return true;
    } else {
        return false;
    }
}
