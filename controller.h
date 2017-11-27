#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QHostInfo>
#include <QHostAddress>

#include "config.h"
#include "serversocket.h"
#include "friendrelation.h"
#include "ratingcalculator.h"
#include "rating.h"

class Controller: public QObject
{
    Q_OBJECT
public:
    Controller();
    void setUp();

public slots:
    void processTheDatagram(const QByteArray&, const QHostAddress&, const quint16&);

private:

    void processFriendRequest(const QVariantMap&);
    void processUserFeedback(const QVariantMap&);
    void processFileRatingRequest(const QVariantMap&, const QHostAddress&, const quint16&);

    void addFriendRelation(const QString& userName, const QString& friendName);


    ServerSocket* sock;

    FriendRelation* friendRelation;
    Rating* rating;

    QMap<QString, QSet<QString>> friendRequest; // ?????

    RatingCalculator* ratingCalculator;




};

#endif // CONTROLLER_H
