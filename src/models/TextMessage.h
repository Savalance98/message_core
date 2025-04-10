#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include "Message.h"
#include <string>

class TextMessage : public Message {
public:
    TextMessage(const std::string& text);
    std::string get_text() const override;

private:
    std::string text;
};

#endif