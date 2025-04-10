#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message {
public:
    virtual ~Message() = default;
    virtual std::string get_text() const = 0;
};

#endif // MESSAGE_H