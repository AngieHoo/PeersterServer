#include "friendrelation.h"

FriendRelation::FriendRelation(QObject *parent)
    :QObject(parent)
{
  QFile requests("friendrequests");
  if(requests.open(QIODevice::ReadOnly)) 
  {
    qDebug()<<"friendrqeusts file exists, reading input";
    QDataStream requestsIn(&requests);
    requestsIn >> friendRequest;
    requests.close();
  }
  else
  {
    qDebug()<<"friendrequests file do not exist";
  }

  QFile lists("friendlists");
  if (lists.open(QIODevice::ReadOnly))
  {
    qDebug()<<"friendlists file exists, reading input";
    QDataStream listsIn(&lists);
    listsIn >> friendList;
    lists.close();
  }
  else
  {
    qDebug()<<"friendlists file does not exist";
  }
}

FriendRelation::~FriendRelation()
{
  storeLocal();
}

QSet<QString> FriendRelation::getFriendList(const QString &userName)
{
    return friendList.value(userName);
}

bool FriendRelation::addFriendRelation(const QString &userName1, const QString &userName2)
{
  QString tmp1 = userName1.compare(userName2, Qt::CaseInsensitive) < 0 ? userName1 : userName2;
  QString tmp2 = userName1.compare(userName2, Qt::CaseInsensitive) < 0 ? userName2 : userName1;
//Comparing the names so request are always in alphabetical order, so we don't need to check existence of request key twice
  if (friendRequest.contains(tmp1))
    {
      if (friendRequest.value(tmp1).contains(tmp2)) 
      {//there is a request between same two users, add them to friend list of each other
        friendRequest[tmp1].remove(tmp2);
        if (friendRequest.value(tmp1).empty()) {
          friendRequest.remove(tmp1);
        }
        
        if (friendList.contains(tmp1) && 
            !friendList.value(tmp1).contains(tmp2)) 
        {
          friendList[tmp1].insert(tmp2);
        } 
        else if (!friendList.contains(tmp1)) 
        {
          QSet<QString> v;
          v.insert(tmp2);
          friendList.insert(tmp1, v);
        }

        if (friendList.contains(tmp2) && 
            !friendList.value(tmp2).contains(tmp1)) 
        {
          friendList[tmp2].insert(tmp1);
        } 
        else if (!friendList.contains(tmp2)) 
        {
          QSet<QString> v;
          v.insert(tmp1);
          friendList.insert(tmp2, v);
        }

        return true;
      }
      else
      {
        friendRequest[tmp1].insert(tmp2);
        return false;
      }
  
    }
  else 
    {
      QSet<QString> v;
      v.insert(tmp2);
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
  requests.open(QIODevice::WriteOnly);
  QDataStream requestsOut(&requests);
  requestsOut << friendRequest;
  requests.close();

  QFile lists("friendlists");
  lists.open(QIODevice::WriteOnly);
  QDataStream listsOut(&lists);
  listsOut << friendList;
  lists.close();
}
