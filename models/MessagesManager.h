#ifndef MessagesManager_H
#define MessagesManager_H
#include <vector>
#include <iostream>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"
#include "dependencies/CoreDependencies.h"


class Message_manager {
private:
std::shared_ptr<CoreDependencies> deps;
public:
    explicit Message_manager(std::shared_ptr<CoreDependencies> deps_);
    void send_message(const std::string& msg, const std::string& ip);

private:
    void handle_incoming_message(const std::string& msg, const std::string& sender);

};

#endif