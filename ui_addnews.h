/********************************************************************************
** Form generated from reading UI file 'addnews.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWS_H
#define UI_ADDNEWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addNews
{
public:
    QLineEdit *SearchLineEdit;
    QPushButton *searchPushButton;
    QLabel *headLabel;
    QLabel *nameLabel;
    QLabel *signalLabel;
    QLabel *vTitleLabel;
    QTextEdit *verifyTextEdit;
    QLineEdit *remarkLineEdit;
    QLabel *rTitleLabel;
    QLabel *gTitleLabel;
    QComboBox *groupComboBox;
    QPushButton *sendPushButton;

    void setupUi(QWidget *addNews)
    {
        if (addNews->objectName().isEmpty())
            addNews->setObjectName(QStringLiteral("addNews"));
        addNews->resize(379, 348);
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(11);
        addNews->setFont(font);
        SearchLineEdit = new QLineEdit(addNews);
        SearchLineEdit->setObjectName(QStringLiteral("SearchLineEdit"));
        SearchLineEdit->setGeometry(QRect(10, 10, 251, 29));
        searchPushButton = new QPushButton(addNews);
        searchPushButton->setObjectName(QStringLiteral("searchPushButton"));
        searchPushButton->setGeometry(QRect(270, 10, 81, 30));
        headLabel = new QLabel(addNews);
        headLabel->setObjectName(QStringLiteral("headLabel"));
        headLabel->setGeometry(QRect(20, 73, 60, 55));
        nameLabel = new QLabel(addNews);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setGeometry(QRect(110, 70, 91, 26));
        signalLabel = new QLabel(addNews);
        signalLabel->setObjectName(QStringLiteral("signalLabel"));
        signalLabel->setGeometry(QRect(110, 103, 221, 26));
        vTitleLabel = new QLabel(addNews);
        vTitleLabel->setObjectName(QStringLiteral("vTitleLabel"));
        vTitleLabel->setGeometry(QRect(20, 150, 221, 26));
        verifyTextEdit = new QTextEdit(addNews);
        verifyTextEdit->setObjectName(QStringLiteral("verifyTextEdit"));
        verifyTextEdit->setGeometry(QRect(20, 180, 331, 81));
        remarkLineEdit = new QLineEdit(addNews);
        remarkLineEdit->setObjectName(QStringLiteral("remarkLineEdit"));
        remarkLineEdit->setGeometry(QRect(60, 270, 111, 27));
        rTitleLabel = new QLabel(addNews);
        rTitleLabel->setObjectName(QStringLiteral("rTitleLabel"));
        rTitleLabel->setGeometry(QRect(20, 270, 41, 26));
        gTitleLabel = new QLabel(addNews);
        gTitleLabel->setObjectName(QStringLiteral("gTitleLabel"));
        gTitleLabel->setGeometry(QRect(180, 270, 41, 26));
        groupComboBox = new QComboBox(addNews);
        groupComboBox->setObjectName(QStringLiteral("groupComboBox"));
        groupComboBox->setGeometry(QRect(220, 270, 131, 27));
        sendPushButton = new QPushButton(addNews);
        sendPushButton->setObjectName(QStringLiteral("sendPushButton"));
        sendPushButton->setGeometry(QRect(20, 310, 331, 30));

        retranslateUi(addNews);

        QMetaObject::connectSlotsByName(addNews);
    } // setupUi

    void retranslateUi(QWidget *addNews)
    {
        addNews->setWindowTitle(QApplication::translate("addNews", "Form", Q_NULLPTR));
        searchPushButton->setText(QApplication::translate("addNews", "\346\220\234\347\264\242", Q_NULLPTR));
        headLabel->setText(QString());
        nameLabel->setText(QString());
        signalLabel->setText(QString());
        vTitleLabel->setText(QApplication::translate("addNews", "\351\252\214\350\257\201\344\277\241\346\201\257", Q_NULLPTR));
        rTitleLabel->setText(QApplication::translate("addNews", "\345\244\207\346\263\250", Q_NULLPTR));
        gTitleLabel->setText(QApplication::translate("addNews", "\345\210\206\347\273\204", Q_NULLPTR));
        groupComboBox->clear();
        groupComboBox->insertItems(0, QStringList()
         << QApplication::translate("addNews", "\346\210\221\347\232\204\345\245\275\345\217\213", Q_NULLPTR)
        );
        sendPushButton->setText(QApplication::translate("addNews", "\345\217\221\351\200\201\347\224\263\350\257\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addNews: public Ui_addNews {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWS_H
