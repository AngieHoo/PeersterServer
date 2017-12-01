#ifndef FRIENDRELATION_H
#define FRIENDRELATION_H
#include <QObject>
#include <QVector>
#include <QMap>
#include <QFile>
#include <QDataStream>
#include <QSet>


class FriendRelation: public QObject
{
    Q_OBJECT
public:
    FriendRelation(QObject *parent = 0);
    QSet<QString> getFriendList(const QString& userName);
    bool addFriendRelation(const QString& userName1, const QString& userName2);
    bool areFriends(const QString& userName1, const QString& userName2);
    void storeLocal();

    QMap<QString, QSet<QString>> friendList;
    QMap<QString, QSet<QString>> friendRequest;
    
};

#endif // FRIENDRELATION_H
