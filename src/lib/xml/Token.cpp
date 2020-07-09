#include "xml/Token.h"

std::ostream& operator<<(std::ostream &stream, const Token &token) {
    stream << token.str;
    return stream;
}

bool Token::operator==(const Token &other) const {
    return (this->type == other.type) && (this->str == other.str);
}

bool Token::operator!=(const Token &other) const {
    return !(*this == other);
}
