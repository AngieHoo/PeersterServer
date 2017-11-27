#ifndef LIB_H
#define LIB_H
#include <QString>

typedef enum {
    FRIEND_REQUEST = 0,
    RATING_FEEDBACK,
    SCORE_REQUEST
}messageType;

const QString USER_NAME = "UserName";
const QString FRIEND_NAME = "FriendName";
const QString FILE_ID= "FileId";
const QString SCORE= "Score";

const quint16 PORT = 32768;

const QString FRIEND_RELATION_FILE_PATH = "./friend.txt";
const QString RATING_FILE_PATH = "./rating.txt";

#endif // LIB_H
