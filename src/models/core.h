#ifndef CORE_H
#define CORE_H

#include <memory>
#include <string>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"
#include "models/MessagesManager.h"
// #include "models/UsersManager.h"
// #include "db/DBManager.h"
#include "CoreDependencies.h"

class Core {
public:
    Core(std::shared_ptr<DB> db_,
         std::shared_ptr<http_server> http_);

    // Геттеры для доступа к менеджерам
    std::unique_ptr<Message_manager>& get_messages_manager() {
        return messagesManager;
    }

    // std::unique_ptr<DB_manager>& get_db_manager() {
    //     return dbManager;
    // }

private:
    std::unique_ptr<Message_manager> messagesManager;
    // std::unique_ptr<DB_manager>      dbManager;
    std::shared_ptr<CoreDependencies> dependencies;
};

#endif
