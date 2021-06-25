/********************************************************************************
** Form generated from reading UI file 'agreefriend.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGREEFRIEND_H
#define UI_AGREEFRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_agreeFriend
{
public:
    QListView *listView;
    QLineEdit *nickLineEdit;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_2;
    QPushButton *disagreePushButton;
    QPushButton *agreePushButton;
    QLabel *head;
    QLabel *nickName;
    QLabel *intro;

    void setupUi(QWidget *agreeFriend)
    {
        if (agreeFriend->objectName().isEmpty())
            agreeFriend->setObjectName(QStringLiteral("agreeFriend"));
        agreeFriend->resize(228, 300);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(10);
        agreeFriend->setFont(font);
        listView = new QListView(agreeFriend);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(0, 0, 231, 301));
        nickLineEdit = new QLineEdit(agreeFriend);
        nickLineEdit->setObjectName(QStringLiteral("nickLineEdit"));
        nickLineEdit->setGeometry(QRect(320, 150, 151, 26));
        comboBox = new QComboBox(agreeFriend);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(320, 210, 151, 26));
        label = new QLabel(agreeFriend);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(280, 153, 41, 21));
        label_2 = new QLabel(agreeFriend);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 213, 41, 21));
        disagreePushButton = new QPushButton(agreeFriend);
        disagreePushButton->setObjectName(QStringLiteral("disagreePushButton"));
        disagreePushButton->setGeometry(QRect(400, 260, 75, 26));
        agreePushButton = new QPushButton(agreeFriend);
        agreePushButton->setObjectName(QStringLiteral("agreePushButton"));
        agreePushButton->setGeometry(QRect(280, 260, 75, 26));
        head = new QLabel(agreeFriend);
        head->setObjectName(QStringLiteral("head"));
        head->setGeometry(QRect(270, 60, 54, 51));
        nickName = new QLabel(agreeFriend);
        nickName->setObjectName(QStringLiteral("nickName"));
        nickName->setGeometry(QRect(350, 60, 54, 16));
        intro = new QLabel(agreeFriend);
        intro->setObjectName(QStringLiteral("intro"));
        intro->setGeometry(QRect(350, 90, 54, 16));

        retranslateUi(agreeFriend);

        QMetaObject::connectSlotsByName(agreeFriend);
    } // setupUi

    void retranslateUi(QWidget *agreeFriend)
    {
        agreeFriend->setWindowTitle(QApplication::translate("agreeFriend", "Form", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("agreeFriend", "\346\210\221\347\232\204\345\245\275\345\217\213", Q_NULLPTR)
        );
        label->setText(QApplication::translate("agreeFriend", "\345\244\207\346\263\250", Q_NULLPTR));
        label_2->setText(QApplication::translate("agreeFriend", "\345\210\206\347\273\204", Q_NULLPTR));
        disagreePushButton->setText(QApplication::translate("agreeFriend", "\346\213\222\347\273\235", Q_NULLPTR));
        agreePushButton->setText(QApplication::translate("agreeFriend", "\345\212\240\345\245\275\345\217\213", Q_NULLPTR));
        head->setText(QString());
        nickName->setText(QApplication::translate("agreeFriend", "name", Q_NULLPTR));
        intro->setText(QApplication::translate("agreeFriend", "sign", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class agreeFriend: public Ui_agreeFriend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGREEFRIEND_H
