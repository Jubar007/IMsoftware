#ifndef USERLISTDATA_H
#define USERLISTDATA_H
#include <QString>
#include <QMetaType>

struct UserItemData
{
    QString sHeadPic;
    QString sUserName;
    QString userSignalTrue;

    UserItemData() {
        sHeadPic = "";
        sUserName = "";
        userSignalTrue = "";
    }
};

Q_DECLARE_METATYPE(UserItemData);
#endif // USERLISTDATA_H
