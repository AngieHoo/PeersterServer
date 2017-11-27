#include "controller.h"

Controller::Controller()
{
    sock = new ServerSocket(this);
    connect(sock, SIGNAL(processTheDatagram(QByteArray,QHostAddress,quint16)), SLOT(processTheDatagram(QByteArray,QHostAddress,quint16)));

    friendRelation = new FriendRelation(this);
    ratingCalculator = new RatingCalculator(this);

}

void Controller::setUp()
{
    sock->bind();
}

void Controller::processTheDatagram(const QByteArray & datagram, const QHostAddress & IP, const quint16 & port)
{
    QDataStream in(datagram);
    QVariantMap message;
    in >> message;

    if (message.contains(FRIEND_NAME) && message.contains(USER_NAME)) {// a status message
        processFriendRequest(message);
    }
    else if (message.contains(SCORE) && message.contains(FILE_ID)
             && message.contains(USER_NAME)) { // brocast message to a random neighbor
        processUserFeedback(message);
    }
    else if (message.contains(FILE_ID) &&  message.contains(USER_NAME)) {
        processFileRatingRequest(message, IP, port);
    }
    else {
        qDebug() << message.begin().key();
        qDebug() << "wrong message type!";
    }
    return;
}

void Controller::processFriendRequest(const QVariantMap &m)
{
    QString un = m[USER_NAME].toString(), fn = m[FRIEND_NAME].toString();
    if (friendRequest.contains(fn) && friendRequest[fn].contains(un)) {
        // they can be friends.
        friendRequest[fn].erase(friendRequest[fn].find(un));
        friendRelation->addFriendRelation(un, fn);
    }
    else friendRequest[un].insert(fn);

}

void Controller::processUserFeedback(const QVariantMap &m)
{
    rating->addUserRating(m[FILE_ID].toString(), m[USER_NAME].toString(), m[SCORE].toDouble());
}

void Controller::processFileRatingRequest(const QVariantMap &m, const QHostAddress &IP, const quint16 &port)
{
    QString un = m[USER_NAME].toString(), fileID = m[FILE_ID].toString();

    QVariantMap reply;
    reply[FILE_ID] =  fileID;

    // If user has already rate this file, just return the score.
    if (rating->hasRating(un, fileID)) {
        reply[SCORE] = rating->getUserRating(un, fileID);
    }
    else {
        // If not, use ratingCalculator to predict the score.
        reply[SCORE]  = ratingCalculator->getPredictedRating(fileID, un, friendRelation, rating);
    }

    sock->sendMessage(IP, port, reply);
}
