#ifndef MESSAGERECORD_H
#define MESSAGERECORD_H

#include <string>

class MessageRecord {
public:
    MessageRecord(int id, const std::string& fromUser, const std::string& toUser, 
                  const std::string& message, int status);

    int getId() const;
    std::string getFromUser() const;
    std::string getToUser() const;
    std::string getMessage() const;
    int getStatus() const;

private:
    int id;
    std::string fromUser;
    std::string toUser;
    std::string message;
    int status;
};

#endif // MESSAGERECORD_H