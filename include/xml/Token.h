//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_TOKEN_H
#define XML_DEMON_TOKEN_H

#include <string>
#include <iostream>

struct Token {
    enum Type {
        STRING,
        VARIABLE,
        EQ,
        QUOTE,
        DQUOTE,
        OPEN_QUOTE_BLOCK,
        CLOSE_QUOTE_BLOCK,
        OPEN_QUOTE_END_BLOCK,
        BEGIN_PROLOG,
        END_PROLOG,
        END,
        ERROR

    };
    std::string str;
    Type type;

    bool operator==(const Token &other) const;
    bool operator!=(const Token &other) const;
};

std::ostream& operator<<(std::ostream &stream, const Token &token);
#endif //XML_DEMON_TOKEN_H
