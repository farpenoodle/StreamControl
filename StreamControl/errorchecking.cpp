#include "mainwindow.h"

QStringList MainWindow::checkLayout(QDomDocument doc) {

    QStringList errors;
    QDomElement layout = doc.namedItem("layout").toElement();
    bool intHandler;
    if (layout.isNull()) {
        errors << "Layout element does not exist";
        return errors;
    } else {
        if (!layout.hasAttribute("width"))
            errors << "Layout has no width value";
        if (!layout.hasAttribute("height"))
            errors << "Layout has no height value";
        if (layout.hasAttribute("width") && (layout.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
            errors << "Layout width is not a positive integer";
        if (layout.hasAttribute("width") && (layout.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
            errors << "Layout height is not a positive integer";

        QStringList layouterrors ;

        if(layout.attribute("tabbed") == "1"){
            layouterrors << checkTabLayout(layout);
        } else {
            layouterrors << checkElements(layout);
        }

        errors.append(layouterrors);

    }
    return errors;
}

QStringList MainWindow::checkElements(QDomElement element){
    QDomNode child = element.firstChild();
    QStringList errors;
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();
        if(tagName == "label") {
            errors << checkLabel(child.toElement());
        } else if (tagName == "line") {
            errors << checkLine(child.toElement());
        } else if (tagName == "button") {
            errors << checkButton(child.toElement());
        } else if (tagName == "lineEdit") {
            errors << checkLineEdit(child.toElement());
        } else if (tagName == "spinBox") {
            errors << checkSpinBox(child.toElement());
        } else if (tagName == "checkBox") {
            errors << checkCheckBox(child.toElement());
        } else if (tagName == "radioGroup") {
            errors << checkRadioGroup(child.toElement());
        } else if (tagName == "tweet") {
            errors << checkTweetWidget(child.toElement());
        } else if (tagName == "tabSet") {
            errors << checkTabLayout(child.toElement());
        } else if (tagName == "challongeMatch") {
            errors << checkChallongeWidget(child.toElement());
        } else if (tagName == "cli") {
            //errors << checkCLI(child.toElement());
        }
        child = child.nextSibling();
    }
    return errors;
}

QStringList MainWindow::checkLabel(QDomElement element){
    bool intHandler;
    QStringList errors;
    if (!element.hasAttribute("width"))
        errors << "Label has no width value";
    if (!element.hasAttribute("height"))
        errors << "Label has no height value";
    if (!element.hasAttribute("x"))
        errors << "Label has no x value";
    if (!element.hasAttribute("y"))
        errors << "Label has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Label width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Label height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Label x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Label y is not a positive integer";

    return errors;
}

QStringList MainWindow::checkLine(QDomElement element){
    bool intHandler;
    QStringList errors;

    if (!element.hasAttribute("width"))
        errors << "Line has no width value";
    if (!element.hasAttribute("height"))
        errors << "Line has no height value";
    if (!element.hasAttribute("x"))
        errors << "Line has no x value";
    if (!element.hasAttribute("y"))
        errors << "Line has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Line width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Line height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Line x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Line y is not a positive integer";

    return errors;
}

QStringList MainWindow::checkButton(QDomElement element){
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "Button must have an id";
    if (!element.hasAttribute("width"))
        errors << "Button " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "Button " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "Button " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "Button " + idstr + "has no y value";
    if (!element.hasAttribute("type"))
        errors << "Button " + idstr + "has no type value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Button " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Button " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Button " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Button " + idstr + "y is not a positive integer";
    if (element.hasAttribute("type") && (element.attribute("type") != "reset" && element.attribute("type") != "swap" && element.attribute("type") != "timestamp" && element.attribute("type") != "setButton"))
        errors << "Button " + idstr + "type is not recognised";
    if (element.attribute("type") == "reset" && !element.hasAttribute("reset"))
        errors << "Button " + idstr + "type \"reset\" must have \"reset\" attribute set";
    if (element.attribute("type") == "swap" && (!element.hasAttribute("swapSet1") || !element.hasAttribute("swapSet2")))
        errors << "Button " + idstr + "type \"swap\" must have \"swapSet1\" & \"swapSet2\" attributes set";

    return errors;
}

QStringList MainWindow::checkLineEdit(QDomElement element){
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "LineEdit must have an id";
    if (!element.hasAttribute("width"))
        errors << "LineEdit " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "LineEdit " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "LineEdit " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "LineEdit " + idstr + "has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "LineEdit " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "LineEdit " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "LineEdit " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "LineEdit " + idstr + "y is not a positive integer";

    return errors;
}

QStringList MainWindow::checkSpinBox(QDomElement element){
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "SpinBox must have an id";
    if (!element.hasAttribute("width"))
        errors << "SpinBox " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "SpinBox " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "SpinBox " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "SpinBox " + idstr + "has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "SpinBox " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "SpinBox " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "SpinBox " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "SpinBox " + idstr + "y is not a positive integer";
    if (element.hasAttribute("maximum") && (element.attribute("maximum").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "SpinBox " + idstr + "maximum is not a positive integer";

    return errors;
}

QStringList MainWindow::checkTabLayout(QDomElement element) {
    QDomNode child = element.firstChild();
    QStringList errors;
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();
        if(tagName == "tab") {

            if (!child.toElement().hasAttribute("name"))
                errors << "Tab has no name";

            errors << checkElements(child.toElement());

        } else if (tagName == "cli" || tagName == "toolBar") {
            //ignore these
        } else {
            errors << "Invalid item " + tagName + " in tabSet";
        }

        child = child.nextSibling();
    }
    return errors;
}

QStringList MainWindow::checkCheckBox(QDomElement element){
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "CheckBox must have an id";
    if (!element.hasAttribute("width"))
        errors << "CheckBox " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "CheckBox " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "CheckBox " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "CheckBox " + idstr + "has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "CheckBox " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "CheckBox " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "CheckBox " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "CheckBox " + idstr + "y is not a positive integer";

    return errors;
}

QStringList MainWindow::checkRadioGroup(QDomElement element) {
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "RadioGroup must have an id";
    QDomNode child = element.firstChild();
    int buttonNumber = 1;
    while (!child.isNull()) {
        QString tagName = child.toElement().tagName();
        if(tagName == "radioButton") {
            QDomElement newElement = child.toElement();

            if (!newElement.hasAttribute("width"))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " has no width value";
            if (!newElement.hasAttribute("height"))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " has no height value";
            if (!newElement.hasAttribute("x"))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " has no x value";
            if (!newElement.hasAttribute("y"))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " has no y value";
            if (newElement.hasAttribute("width") && (newElement.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " width is not a positive integer";
            if (newElement.hasAttribute("height") && (newElement.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " height is not a positive integer";
            if (newElement.hasAttribute("x") && (newElement.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " x is not a positive integer";
            if (newElement.hasAttribute("y") && (newElement.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " y is not a positive integer";
            if (!newElement.hasAttribute("value"))
                errors << "RadioGroup " + idstr + "RadioButton " + QString::number(buttonNumber) + " has no value";

        } else {
            errors << "Invalid item " + tagName + " in tabSet";
        }

        child = child.nextSibling();
    }
    return errors;
}

QStringList MainWindow::checkTweetWidget(QDomElement element){
    bool intHandler;
    QStringList errors;
    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "Tweet Widget must have an id";
    if (!element.hasAttribute("width"))
        errors << "Tweet Widget " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "Tweet Widget " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "Tweet Widget " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "Tweet Widget " + idstr + "has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Tweet Widget " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Tweet Widget " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Tweet Widget " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Tweet Widget " + idstr + "y is not a positive integer";

    return errors;
}

QStringList MainWindow::checkChallongeWidget(QDomElement element){
    bool intHandler;
    QStringList errors;

    QString id = element.attribute("id");
    QString idstr;
    if (id.length() > 1) {
        idstr = "\""+id+"\" ";
    }
    if (id.length() < 1)
        errors << "Challonge match widget must have an id";
    if (!element.hasAttribute("width"))
        errors << "Challonge match widget " + idstr + "has no width value";
    if (!element.hasAttribute("height"))
        errors << "Challonge match widget " + idstr + "has no height value";
    if (!element.hasAttribute("x"))
        errors << "Challonge match widget " + idstr + "has no x value";
    if (!element.hasAttribute("y"))
        errors << "Challonge match widget " + idstr + "has no y value";
    if (element.hasAttribute("width") && (element.attribute("width").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Challonge match widget " + idstr + "width is not a positive integer";
    if (element.hasAttribute("height") && (element.attribute("height").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Challonge match widget " + idstr + "height is not a positive integer";
    if (element.hasAttribute("x") && (element.attribute("x").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Challonge match widget " + idstr + "x is not a positive integer";
    if (element.hasAttribute("y") && (element.attribute("y").toInt(&intHandler,10) < 0 || intHandler == false))
        errors << "Challonge match widget " + idstr + "y is not a positive integer";

    return errors;
}
