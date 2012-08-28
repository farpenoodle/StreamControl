#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QMap>
#include "config.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

    void setConfig(QMap<QString, QString> settings);
    QMap<QString, QString> getConfig();

public slots:
    void findXSplit();
    
private:
    QMap<QString, QString> configsettings;
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
