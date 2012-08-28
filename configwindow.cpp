#include "configwindow.h"
#include "ui_configwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    connect(ui->browseButton,SIGNAL( clicked() ),this,SLOT( findXSplit() ));

    ui->xsplitPathTB->setDisabled(true);
    ui->streamControlLabel->setText(QString("StreamControl ") + QString(SC_VERSION) );
    ui->qtLabel->setText(QString("This program uses Qt version ")+ QString(qVersion() + QString(".")) );
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::setConfig(QMap<QString, QString> settings) {

    configsettings = settings;
    ui->xsplitPathTB->setText(configsettings["xsplitPath"]);

}

QMap<QString, QString> ConfigWindow::getConfig() {
    return configsettings;
}

void ConfigWindow::findXSplit() {
    QString XSplit = QFileDialog::getOpenFileName(this, tr("Find XSplit"), configsettings["xsplitPath"], tr("XSplit.Core.exe"));
    if (XSplit != "") {
        XSplit.chop(15);
        XSplit.replace("/","\\");
        ui->xsplitPathTB->setText(XSplit);
    }
}
