#include "rating.h"

Rating::Rating()
{
  QFile fileRatingFile("filereputations");
  if(fileRatingFile.open(QIODevice::ReadOnly))
  {
    QDataStream fileRatingIn(&fileRatingFile);
    fileRatingIn >> fileReputation;
    fileRatingFile.close();
  } 
  
  QFile lists("uservotinglists");
  if (lists.open(QIODevice::ReadOnly))
  {
    QDataStream listsIn(&lists);
    listsIn >> userVotingList;
    lists.close();
  }
}

void Rating::storeLocal()
{
  QFile fileRatingFile("filereputations");
  fileRatingFile.open(QIODevice::WriteOnly);
  QDataStream fileRatingOut(&fileRatingFile);
  fileRatingOut << fileReputation;
  fileRatingFile.close();

  QFile lists("uservotinglists");
  lists.open(QIODevice::WriteOnly);
  QDataStream listsOut(&lists);
  listsOut << userVotingList;
  lists.close();
}

bool Rating::hasRating(const QString &userName, const QString &fileID)
{
  return fileReputation.contains(fileID) && fileReputation.value(fileID).contains(userName); 
}

double Rating::getUserRating(const QString &userName, const QString &fileID)
{
  if (hasRating(userName, fileID))
  {
    return fileReputation.value(fileID).value(userName);
  }
  return 0;
}

bool Rating::addUserRating(const QString &fileID, const QString &userName, double score)
{
  if (fileReputation.contains(fileID))
  {
     if (fileReputation.value(fileID).contains(userName))
     {
       qDebug()<<"file rating already exist";
      return false;
     }
     else
     {
      QMap<QString, double> m;
      m.insert(userName, score);
      fileReputation.insert(fileID, m);
     }
  }
  else
  {
    QMap<QString, double> m;
    m.insert(userName, score);
    fileReputation.insert(fileID, m);
  }

  if (!userVotingList.contains(userName)) 
  {
    QVector<QString> v;
    userVotingList.insert(userName, v);
  }
  userVotingList[userName].append(fileID);
  return true;
}

QVector<QString> Rating::getUser2Files(const QString& username)
{
  return userVotingList.value(username);
}

QMap<QString, double> Rating::getFileRating(const QString& fileid) 
{
  return fileReputation.value(fileid);
}

