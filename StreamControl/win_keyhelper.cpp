#include "win_keyhelper.h"
#include <QKeySequence>
#include "windows.h"

int win_keyhelper::getModifiers(int ks)
{
    int modifier = 0;

    if ((ks & Qt::META) == Qt::META)
        modifier |= MOD_WIN;
    if ((ks & Qt::CTRL) == Qt::CTRL)
        modifier |= MOD_CONTROL;
    if ((ks & Qt::ALT) == Qt::ALT)
        modifier |= MOD_ALT;
    if ((ks & Qt::SHIFT) == Qt::SHIFT)
        modifier |= MOD_SHIFT;

    return modifier;
}

int win_keyhelper::getKey(int ks)
{
    int key = 0;

    ks &= ~(Qt::ShiftModifier | Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier);

    int vk = 0;
    while (vk < 255) {
        if (KeyTbl[vk] == ks)
            break;
        vk++;
    }

    if (vk >= 255) {
        key = ks;
    } else {
        key = vk;
    }

    return key;
}

QString win_keyhelper::getString(int modifiers, int key) {
    QString keystring;
    int qks = 0;
    if ((modifiers & MOD_WIN) == MOD_WIN)
        qks |= Qt::MetaModifier;
    if ((modifiers & MOD_CONTROL) == MOD_CONTROL)
        qks |= Qt::ControlModifier;
    if ((modifiers & MOD_ALT) == MOD_ALT)
        qks |= Qt::AltModifier;
    if ((modifiers & MOD_SHIFT) == MOD_SHIFT)
        qks |= Qt::ShiftModifier;

    int qkey = KeyTbl[key];

    if (qkey == 0) {
        qkey = key;
    }

    qks |= qkey;

    keystring = QKeySequence(qks).toString();

    return keystring;
}

int win_keyhelper::getQKS(int modifiers, int key) {
    //QString keystring;
    int qks = 0;
    if ((modifiers & MOD_WIN) == MOD_WIN)
        qks |= Qt::MetaModifier;
    if ((modifiers & MOD_CONTROL) == MOD_CONTROL)
        qks |= Qt::ControlModifier;
    if ((modifiers & MOD_ALT) == MOD_ALT)
        qks |= Qt::AltModifier;
    if ((modifiers & MOD_SHIFT) == MOD_SHIFT)
        qks |= Qt::ShiftModifier;

    int qkey = KeyTbl[key];

    if (qkey == 0) {
        qkey = key;
    }

    qks |= qkey;

    //return QKeySequence(qks)[0];
    return qks;
}
