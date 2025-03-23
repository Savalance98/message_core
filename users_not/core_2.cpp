// #include "core_2.h"


// Core::Core(std::shared_ptr<User> user_ , std::shared_ptr<db> db_ , std::shared_ptr<http_serv> http_):  
// auto dependencies = std::make_shared<CoreDependencies>(user, db, http);;
// {
//     std::make_unique<MessagesManager>(dependencies);
//     std::make_unique<UsersManager>(dependencies);
//     Message_manager();
//     http_serv->run();
// }


// std::vector<std::string> Core::parser(std::string ip_2с ) {
//     std::string delimiter = ":";
//     std::string token_1 = ip_2.substr(0, ip_2.find(delimiter));
//     std::string token_2 = ip_2.substr(ip_2.find(delimiter)+1, ip_2.size()-1);
//     parse_host.push_back(token_1);
//     parse_host.push_back(token_2);
//     return parse_host;
// }

// void Core::send_message(std::string ip_2, std::strig& message) {
//     parser(ip_2);
//     http_serv->send_message_to_user(parse_host[0], parse_host[1], message);
// }


// void Core::history(std::string ip_2){
//     db->get_element_for_db(user->get_host(), ip_2);
//     // std::cout << "host_1 send " << message << "to host_2"

// }

