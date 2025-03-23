#include "DBManager.h"
#include <iostream>

DB_manager::DB_manager(std::shared_ptr<DB>db_): db(std::move(db_)) {
}

void DB_manager::history(const std::string& ip_2)
{
    // Пример реализации
    // Здесь может быть логика выбора из базы сообщений
    // например, db->get_history(ip_2)
    // и вывод/возврат данных.
    db->get_history(ip_2);
    std::cout << "[DB_manager::history] Fetching history for " << ip_2 << std::endl;

    // Предположим, DB имеет метод get_messages_for_user(ip) -> vector<string>
    // auto messages = db->get_messages_for_user(ip_2);
    // for (auto &msg : messages) {
    //    std::cout << msg << std::endl;
    // }
}