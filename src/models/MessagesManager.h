#ifndef MessagesManager_H
#define MessagesManager_H
#include <vector>
#include <iostream>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"
#include "CoreDependencies.h"
#include <memory>
#include "Message.h"
#include "TextMessage.h"
#include "db/MessageRecord.h"
#include "History.h"


class Message_manager {
private:
std::shared_ptr<CoreDependencies> deps;
public:
    explicit Message_manager(std::shared_ptr<CoreDependencies> deps_);
    void send_message(const std::string& msg, const std::string& ip);
    std::unique_ptr<History> get_history(const std::string& ip_2);
private:
    void handle_incoming_message(const std::string& msg, const std::string& sender);
    std::vector<std::unique_ptr<Message>> convert_records_to_messages(const std::vector<MessageRecord>& records);
};

#endif