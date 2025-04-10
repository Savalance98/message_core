#include "MessageRecord.h"

MessageRecord::MessageRecord(int id, const std::string& fromUser, const std::string& toUser, 
                             const std::string& message, int status)
    : id(id), fromUser(fromUser), toUser(toUser), message(message), status(status) {}

int MessageRecord::getId() const {
    return id;
}

std::string MessageRecord::getFromUser() const {
    return fromUser;
}

std::string MessageRecord::getToUser() const {
    return toUser;
}

std::string MessageRecord::getMessage() const {
    return message;
}

int MessageRecord::getStatus() const {
    return status;
}