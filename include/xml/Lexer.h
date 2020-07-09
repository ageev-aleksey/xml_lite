//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_LEXER_H
#define XML_DEMON_LEXER_H
#include "xml/Token.h"
#include <regex>

class Lexer {
public:
    explicit Lexer(std::string str);
    Token next();
    void back();
private:
    Token parseString();
    Token endProlog();

    enum class State {
        PARSE_PROPERTY_NAME,
        PARSE_PROPERTY_VALUE,
        PARSE_BODY
    };
    enum class  QuoteType : char {
        SINGLE = '\'',
        DOUBLE = '"',
    };

    std::string mStr;
    std::string::iterator  mItr;
    State mState;
    QuoteType mQuoteType;
};


#endif //XML_DEMON_LEXER_H
