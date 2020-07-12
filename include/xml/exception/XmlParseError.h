//
// Created by nrx on 12.07.2020.
//

#ifndef XML_DEMON_XMLPARSEERROR_H
#define XML_DEMON_XMLPARSEERROR_H
#include <stdexcept>
class XmlParserError : public std::runtime_error {
public:
    explicit XmlParserError(const std::string &msg);
};

#endif //XML_DEMON_XMLPARSEERROR_H
