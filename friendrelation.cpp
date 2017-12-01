#include "friendrelation.h"

FriendRelation::FriendRelation(QObject *parent)
    :QObject(parent)
{
  QFile requests("friendrequests");
  if(requests.open(QIODevice::ReadOnly)) 
  {
    QDataStream reqeustsIn(&requests);
    reqeustIn >> friendRequest;
    requests.close();
  }

  QFile lists("friendlists");
  if (lists.open(QIODevice::ReadOnly))
  {
    QDataStream listsIn(&lists);
    listsIn >> freiendList;
    lists.close();
  }
}

QVector<QString> FriendRelation::getFriendList(const QString &userName)
{
    return friendList.value(userName);
}

bool FriendRelation::addFriendRelation(const QString &userName1, const QString &userName2)
{
  QString tmp1 = userName1.compare(userName2, Qt::CaseInsensitive) < 0 ? userName1 : userName2;
  QString tmp2 = userName1.compare(userName2, Qt::CaseInsensitive) < 0 ? userName2 : userName1;
//Comparing the names so request are always in alphabetical order, so we don't need to check existence of request key twice
  if (frienRequest.contains(tmp1)
    {
      if (frienRequest.value(tmp1).contains(tmp2)) 
      {//there is a request between same two users, add them to friend list of each other
        friendRequest.value(tmp1).remove(tmp2);
        if (frienduest.value(tmp1).empty()) {
          friendRequest.remvoe(tmp1);
        }
        
        if (friendList.contains(tmp1) && 
            !friendList.value(tmp1).contains(tmp2)) 
        {
          friendList.value(tmp1).append(tmp2);
        } 
        else if (!friendList.contains(tmp1)) 
        {
          QVector<QString> v;
          v.append(tmp2);
          friendList.insert(tmp1, v);
        }

        if (friendList.contains(tmp2) && 
            !friendList.value(tmp2).contains(tmp1)) 
        {
          friendList.value(tmp2).append(tmp1);
        } 
        else if (!friendList.contains(tmp2)) 
        {
          QVector<QString> v;
          v.append(tmp1);
          friendList.insert(tmp2, v);
        }

        return true;
      }
      else
      {
        friendRequest.vlaue(tmp1).insert(tmp2);
        return false;
      }
  
    }
  else 
    {
      QVector<QString> v;
      v.append(tmp2);
      friendRequest.insert(tmp1, v);
      return false;
    }

}

bool FriendRelation::areFriends(const QString &userName1, const QString &userName2)
{
  return friendList.value(userName1).contains(userName2);
}

void FriendRelation::storeLocal()
{
  QFile requests("friendrequests");
  rquests.open(QIODevice::WriteOnly);
  QDataStream requestsOut(&requests);
  out << friendRequest;
  requests.close();

  QFile lists("friendlists");
  lists.open(QIODevice::WriteOnly);
  QDataStream listsOut(&lists);
  out << friendList;
  lists.close();
}
