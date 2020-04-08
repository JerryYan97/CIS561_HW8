/********************************************************************************
** Form generated from reading UI file 'errorwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORWINDOW_H
#define UI_ERRORWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorWindow
{
public:
    QLabel *label;

    void setupUi(QWidget *ErrorWindow)
    {
        if (ErrorWindow->objectName().isEmpty())
            ErrorWindow->setObjectName(QStringLiteral("ErrorWindow"));
        ErrorWindow->resize(400, 300);
        ErrorWindow->setStyleSheet(QStringLiteral("background-color: yellow;"));
        label = new QLabel(ErrorWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 391, 291));
        QFont font;
        font.setFamily(QStringLiteral("Comic Sans MS"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("QLabel {\n"
"	font: \"Comic Sans MS\";\n"
"	color: magenta;\n"
"}\n"
""));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(ErrorWindow);

        QMetaObject::connectSlotsByName(ErrorWindow);
    } // setupUi

    void retranslateUi(QWidget *ErrorWindow)
    {
        ErrorWindow->setWindowTitle(QApplication::translate("ErrorWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ErrorWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ErrorWindow: public Ui_ErrorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORWINDOW_H
