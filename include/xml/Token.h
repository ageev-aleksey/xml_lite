//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_TOKEN_H
#define XML_DEMON_TOKEN_H

#include <string>
#include <iostream>

/**
 * @brief Токены, на которые выполняется разбивка xml документа.
 */
struct Token {
    /**
     * @brief Тип токена
     */
    enum Type {
        /// строка текста, встречается в теле тега и в значениях свойствю
        STRING,
        /// название тега или название ствойства
        VARIABLE,
        /// символ '='
        EQ,
        /// символ '''
        QUOTE,
        /// символ '"'
        DQUOTE,
        /// символ '<'
        OPEN_QUOTE_BLOCK,
        /// символ '>'
        CLOSE_QUOTE_BLOCK,
        /// символ '</'
        OPEN_QUOTE_END_BLOCK,
        /// символ '<?xml'
        BEGIN_PROLOG,
        /// символ '?>'
        END_PROLOG,
        /// конец потока токенов
        END,
        /// ошибка разбора
        ERROR
    };
    /// строковое представление токена
    std::string str;
    /// тип токена
    Type type;

    bool operator==(const Token &other) const;
    bool operator!=(const Token &other) const;
};

/**
 * @brief Оператор вывода токена в поток.
 * @param stream - поток.
 * @param token - токен.
 * @return поток.
 */
std::ostream& operator<<(std::ostream &stream, const Token &token);
#endif //XML_DEMON_TOKEN_H
