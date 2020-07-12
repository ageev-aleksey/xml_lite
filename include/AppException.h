//
// Created by nrx on 12.07.2020.
//

#ifndef XML_DEMON_APPEXCEPTION_H
#define XML_DEMON_APPEXCEPTION_H
#include <stdexcept>

class AppException : public std::runtime_error {
public:
    explicit AppException(const std::string &msg);
};

#endif //XML_DEMON_APPEXCEPTION_H
