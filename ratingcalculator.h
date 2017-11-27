#ifndef RATINGPREDICTOR_H
#define RATINGPREDICTOR_H
#include <QObject>
#include "friendrelation.h"
#include "rating.h"

class RatingCalculator: public QObject
{
    Q_OBJECT
public:
    RatingCalculator(QObject *parent = 0);
    double getPredictedRating(const QString& userName, const QString& fileId, FriendRelation* friendRelation, Rating* rating);

private:
    double getSimilarity(const QString& u1, const QString& u2);


};

#endif // RATINGPREDICTOR_H
