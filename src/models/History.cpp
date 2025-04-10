#include "History.h"

History::History(std::vector<std::unique_ptr<Message>> messages) : allMessages(std::move(messages)) {}

std::vector<std::string> History::get_messages() const {
    std::vector<std::string> texts;
    for (const auto& msg : allMessages) {
        texts.push_back(msg->get_text());
    }
    return texts;
}

std::vector<std::string> History::get_messages(int k) const {
    if (k <= 0) return {};
    size_t count = std::min(static_cast<size_t>(k), allMessages.size());
    std::vector<std::string> texts;
    for (auto it = allMessages.end() - count; it != allMessages.end(); ++it) {
        texts.push_back((*it)->get_text());
    }
    return texts;
}