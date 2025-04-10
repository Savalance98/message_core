#ifndef HISTORY_H
#define HISTORY_H

#include "Message.h"
#include <vector>
#include <memory>

class History {
public:
    History(std::vector<std::unique_ptr<Message>> messages);
    std::vector<std::string> get_messages() const;
    std::vector<std::string> get_messages(int k) const;

private:
    std::vector<std::unique_ptr<Message>> allMessages;
};

#endif // HISTORY_H