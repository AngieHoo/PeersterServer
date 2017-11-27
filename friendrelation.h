#ifndef FRIENDRELATION_H
#define FRIENDRELATION_H
#include <QObject>
#include <QVector>

class FriendRelation: public QObject
{
    Q_OBJECT
public:
    FriendRelation(QObject *parent = 0);
    QVector<QString> getFriendList(const QString& userName);
    bool addFriendRelation(const QString& userName1, const QString& userName2);
    bool areFriends(const QString& userName1, const QString& userName2);

};

#endif // FRIENDRELATION_H
