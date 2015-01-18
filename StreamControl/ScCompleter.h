#ifndef SCCOMPLETER_H
#define SCCOMPLETER_H

#include <QCompleter>



    class ScCompleter : public QCompleter
    {
        Q_OBJECT

    public:
        ScCompleter(QObject* parent = 0);

    private:
        QString widgetName;
        QString dataSetName;
        int dataSetField;
        bool hMaster;

    signals:

    public slots:
        void setName(QString,QString,int,bool);
        QString getName();
        QString getDataSetName();
        int getDataField();
        bool hasMaster();

    };


#endif // SCCOMPLETER_H

