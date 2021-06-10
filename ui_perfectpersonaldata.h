/********************************************************************************
** Form generated from reading UI file 'perfectpersonaldata.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PERFECTPERSONALDATA_H
#define UI_PERFECTPERSONALDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_perfectPersonalData
{
public:
    QPushButton *savePushButton;
    QPushButton *closePushButton;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *synopsisTextEdit;
    QLineEdit *NicknameLineEdit;
    QLabel *label_3;
    QComboBox *sexComboBox;
    QLabel *label_4;
    QLineEdit *phoneLineEdit;
    QLabel *label_5;
    QLineEdit *EmailLneEdit;
    QDateTimeEdit *birthDateTimeEdit;
    QLabel *label_6;

    void setupUi(QWidget *perfectPersonalData)
    {
        if (perfectPersonalData->objectName().isEmpty())
            perfectPersonalData->setObjectName(QStringLiteral("perfectPersonalData"));
        perfectPersonalData->resize(400, 323);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        perfectPersonalData->setFont(font);
        savePushButton = new QPushButton(perfectPersonalData);
        savePushButton->setObjectName(QStringLiteral("savePushButton"));
        savePushButton->setGeometry(QRect(180, 280, 91, 31));
        closePushButton = new QPushButton(perfectPersonalData);
        closePushButton->setObjectName(QStringLiteral("closePushButton"));
        closePushButton->setGeometry(QRect(290, 280, 91, 31));
        label = new QLabel(perfectPersonalData);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 136, 61, 20));
        label_2 = new QLabel(perfectPersonalData);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 22, 61, 20));
        synopsisTextEdit = new QTextEdit(perfectPersonalData);
        synopsisTextEdit->setObjectName(QStringLiteral("synopsisTextEdit"));
        synopsisTextEdit->setGeometry(QRect(20, 160, 361, 101));
        NicknameLineEdit = new QLineEdit(perfectPersonalData);
        NicknameLineEdit->setObjectName(QStringLiteral("NicknameLineEdit"));
        NicknameLineEdit->setGeometry(QRect(55, 22, 121, 22));
        label_3 = new QLabel(perfectPersonalData);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 22, 61, 20));
        sexComboBox = new QComboBox(perfectPersonalData);
        sexComboBox->setObjectName(QStringLiteral("sexComboBox"));
        sexComboBox->setGeometry(QRect(250, 22, 121, 22));
        sexComboBox->setEditable(true);
        sexComboBox->setFrame(true);
        label_4 = new QLabel(perfectPersonalData);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(194, 98, 61, 20));
        phoneLineEdit = new QLineEdit(perfectPersonalData);
        phoneLineEdit->setObjectName(QStringLiteral("phoneLineEdit"));
        phoneLineEdit->setGeometry(QRect(250, 98, 131, 22));
        label_5 = new QLabel(perfectPersonalData);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 98, 61, 20));
        EmailLneEdit = new QLineEdit(perfectPersonalData);
        EmailLneEdit->setObjectName(QStringLiteral("EmailLneEdit"));
        EmailLneEdit->setGeometry(QRect(55, 98, 131, 22));
        birthDateTimeEdit = new QDateTimeEdit(perfectPersonalData);
        birthDateTimeEdit->setObjectName(QStringLiteral("birthDateTimeEdit"));
        birthDateTimeEdit->setGeometry(QRect(55, 60, 194, 22));
        label_6 = new QLabel(perfectPersonalData);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 60, 61, 20));

        retranslateUi(perfectPersonalData);

        QMetaObject::connectSlotsByName(perfectPersonalData);
    } // setupUi

    void retranslateUi(QWidget *perfectPersonalData)
    {
        perfectPersonalData->setWindowTitle(QApplication::translate("perfectPersonalData", "Form", Q_NULLPTR));
        savePushButton->setText(QApplication::translate("perfectPersonalData", "\344\277\235 \345\255\230", Q_NULLPTR));
        closePushButton->setText(QApplication::translate("perfectPersonalData", "\345\205\263 \351\227\255", Q_NULLPTR));
        label->setText(QApplication::translate("perfectPersonalData", "\344\270\252\344\272\272\347\256\200\344\273\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("perfectPersonalData", "\346\230\265\347\247\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("perfectPersonalData", "\346\200\247\345\210\253", Q_NULLPTR));
        sexComboBox->clear();
        sexComboBox->insertItems(0, QStringList()
         << QApplication::translate("perfectPersonalData", "\347\224\267", Q_NULLPTR)
         << QApplication::translate("perfectPersonalData", "\345\245\263", Q_NULLPTR)
         << QApplication::translate("perfectPersonalData", "\346\234\252\347\237\245", Q_NULLPTR)
        );
        sexComboBox->setCurrentText(QApplication::translate("perfectPersonalData", "\347\224\267", Q_NULLPTR));
        label_4->setText(QApplication::translate("perfectPersonalData", "\350\201\224\347\263\273\346\226\271\345\274\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("perfectPersonalData", "\351\202\256\347\256\261", Q_NULLPTR));
        label_6->setText(QApplication::translate("perfectPersonalData", "\347\224\237\346\227\245", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class perfectPersonalData: public Ui_perfectPersonalData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PERFECTPERSONALDATA_H
