#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <filesystem>
#include "MessageRecord.h"
#include <vector>


class DB {
public:
    DB(const std::string& dbname_, const std::string& ip_);
    ~DB();


    void add_message(const std::string& from, 
                     const std::string& to,
                     const std::string& message);

    std::vector<MessageRecord> get_message_records(const std::string& fromUser, const std::string& toUser);
    // void get_history(const std::string& peer);
    sqlite3*& get_db_connectin();
    std::string get_ip_address() const;

private:

    void create_tables();

private:
    std::string dbname;
    std::string db_path;
    std::string ip_address;
    sqlite3* db;
};

#endif
