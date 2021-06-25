/********************************************************************************
** Form generated from reading UI file 'friendgroup.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDGROUP_H
#define UI_FRIENDGROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_friendGroup
{
public:
    QLineEdit *lineEdit;
    QPushButton *addGPushButton;
    QComboBox *comboBox;
    QPushButton *OKPushButton;

    void setupUi(QWidget *friendGroup)
    {
        if (friendGroup->objectName().isEmpty())
            friendGroup->setObjectName(QStringLiteral("friendGroup"));
        friendGroup->resize(333, 130);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        friendGroup->setFont(font);
        lineEdit = new QLineEdit(friendGroup);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 30, 171, 25));
        addGPushButton = new QPushButton(friendGroup);
        addGPushButton->setObjectName(QStringLiteral("addGPushButton"));
        addGPushButton->setGeometry(QRect(210, 30, 75, 26));
        comboBox = new QComboBox(friendGroup);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(20, 80, 171, 25));
        OKPushButton = new QPushButton(friendGroup);
        OKPushButton->setObjectName(QStringLiteral("OKPushButton"));
        OKPushButton->setGeometry(QRect(210, 80, 75, 26));

        retranslateUi(friendGroup);

        QMetaObject::connectSlotsByName(friendGroup);
    } // setupUi

    void retranslateUi(QWidget *friendGroup)
    {
        friendGroup->setWindowTitle(QApplication::translate("friendGroup", "Form", Q_NULLPTR));
        addGPushButton->setText(QApplication::translate("friendGroup", "\346\267\273\345\212\240\345\210\206\347\273\204", Q_NULLPTR));
        OKPushButton->setText(QApplication::translate("friendGroup", "\345\256\214\346\210\220", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class friendGroup: public Ui_friendGroup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDGROUP_H
