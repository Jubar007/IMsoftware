/********************************************************************************
** Form generated from reading UI file 'changeremark.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEREMARK_H
#define UI_CHANGEREMARK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_changeRemark
{
public:
    QPushButton *OKPushButton;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QWidget *changeRemark)
    {
        if (changeRemark->objectName().isEmpty())
            changeRemark->setObjectName(QStringLiteral("changeRemark"));
        changeRemark->resize(279, 87);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        changeRemark->setFont(font);
        OKPushButton = new QPushButton(changeRemark);
        OKPushButton->setObjectName(QStringLiteral("OKPushButton"));
        OKPushButton->setGeometry(QRect(100, 50, 75, 23));
        label = new QLabel(changeRemark);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 54, 21));
        lineEdit = new QLineEdit(changeRemark);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(70, 20, 161, 21));

        retranslateUi(changeRemark);

        QMetaObject::connectSlotsByName(changeRemark);
    } // setupUi

    void retranslateUi(QWidget *changeRemark)
    {
        changeRemark->setWindowTitle(QApplication::translate("changeRemark", "Form", Q_NULLPTR));
        OKPushButton->setText(QApplication::translate("changeRemark", "\345\256\214\346\210\220", Q_NULLPTR));
        label->setText(QApplication::translate("changeRemark", "\345\244\207\346\263\250\345\220\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class changeRemark: public Ui_changeRemark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEREMARK_H
