#include "MessagesManager.h"
#include <iostream>

Message_manager::Message_manager(std::shared_ptr<CoreDependencies> deps_) : deps(deps_)
    {

        deps->http_serv->set_request_handler(
            [this](const std::string& msg, const std::string& sender) {
                handle_incoming_message(msg, sender);
            });
    }

std::vector<std::unique_ptr<Message>> Message_manager::convert_records_to_messages(const std::vector<MessageRecord>& records){
    std::vector<std::unique_ptr<Message>> messages;
    for (const auto& record : records) {
        messages.push_back(std::make_unique<TextMessage>(record.getMessage()));
    }
    return messages;
}

void Message_manager::send_message(const std::string& msg, const std::string& ip_port) {
    size_t colon_pos = ip_port.find(':');
    if (colon_pos == std::string::npos) {
        throw std::runtime_error("Invalid endpoint format. Expected 'IP:PORT'.");
    }

    std::string ip = ip_port.substr(0, colon_pos);
    std::string port = ip_port.substr(colon_pos + 1);


    deps->db->add_message(deps->db->get_ip_address(), ip_port, msg);
    deps->http_serv->send_message(msg, ip, port);
}



void Message_manager::handle_incoming_message(const std::string& msg, const std::string& sender) {
        // std::cout << msg << std::endl;
        deps->db->add_message(sender, deps->db->get_ip_address(), msg);
    }

std::unique_ptr<History> Message_manager::get_history(const std::string& ip_2) {
    std::string fromUser = deps->db->get_ip_address();
    auto records = deps->db->get_message_records(fromUser, ip_2);
    auto messages = convert_records_to_messages(records);
    return std::make_unique<History>(std::move(messages));
}









// std::vector<std::string> Message_manager::parser(const std::string& ip_2)
// {
//     // Перед парсингом лучше очистить вектор,
//     // чтобы при повторном вызове не накапливать старые данные
//     parse_host.clear();

//     std::string delimiter = ":";
//     auto pos = ip_2.find(delimiter);
//     if (pos != std::string::npos) {
//         std::string token_1 = ip_2.substr(0, pos);
//         std::string token_2 = ip_2.substr(pos + delimiter.size());
//         parse_host.push_back(token_1);
//         parse_host.push_back(token_2);
//     } else {
//         // Можно обработать ситуацию, когда в ip_2 нет двоеточия
//         std::cerr << "[parser] Warning: no ':' found in '" << ip_2 << "'\n";
//     }

//     return parse_host; 
// }

// void Message_manager::send_message(const std::string& ip_2, const std::string& message)
// {
//     // Парсим ip:port
//     auto tokens = parser(ip_2);
//     // tokens[0] = ip, tokens[1] = port (если всё прошло успешно)
//     if (tokens.size() >= 2) {
//         // Отправляем через http
//         deps->http_serv->send_message_to_user(tokens[0], tokens[1], message);
//         // Пишем в БД (например, кто отправил, куда, что именно)
//         deps->db->add_message(deps->http_serv->, ip_2, message);
//     } else {
//         std::cerr << "[send_message] Error: cannot parse ip:port from '" 
//                   << ip_2 << "'\n";
//     }
// }
