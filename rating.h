#ifndef RATING_H
#define RATING_H
#include <QObject>

class Rating: public QObject
{
    Q_OBJECT
public:
    Rating();
    bool hasRating(const QString&userName, const QString& fileID);
    double getUserRating(const QString&userName, const QString& fileID);
    bool addUserRating(const QString& fileID, const QString&userName, double score);

};

#endif // RATING_H
