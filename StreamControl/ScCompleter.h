#ifndef SCCOMPLETER_H
#define SCCOMPLETER_H

#include <QCompleter>



    class ScCompleter : public QCompleter
    {
        Q_OBJECT

    public:
        ScCompleter(QObject* parent = 0);

    private:
        QString lineEditName;
        QString dataSetName;

    signals:

    public slots:
        void setName(QString,QString);
        QString getName();
        QString getSetName();

    };


#endif // SCCOMPLETER_H

