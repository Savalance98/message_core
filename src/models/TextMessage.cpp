#include "TextMessage.h"

TextMessage::TextMessage(const std::string& text) : text(text) {}

std::string TextMessage::get_text() const {
    return text;
}