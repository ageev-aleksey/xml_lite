//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_LEXER_H
#define XML_DEMON_LEXER_H
#include "xml/Token.h"
#include <regex>

/**
 * @brief класс выполняющий разбивку xml текста на токены
 */
class Lexer {
public:
    /**
     * @param str - строка в xml формате
     */
    explicit Lexer(std::string str);
    Lexer(const Lexer &lexer);
    Lexer(Lexer &&lexer);
    /**
     * @brief получение следующего токена
     * @return токен
     */
    Token next();
    /**
     * @brief возрат состояния лексера на один шаг назад. Вернуться на два шага назад невозможно.
     */
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
    struct LexerState {
        std::string::iterator  mItr;
        State mState;
        QuoteType mQuoteType;
    };
    std::string mStr;
    LexerState mData;
    LexerState mBeforeState;
};


#endif //XML_DEMON_LEXER_H
