//
// Created by nrx on 11.07.2020.
//

#ifndef XML_DEMON_PARAMTEXT_H
#define XML_DEMON_PARAMTEXT_H

#include <string>

struct ParamText {
    std::string name;
    std::string date; //todo chrono maketime
    size_t hoursWorked;
    bool carTrue;
};

#endif //XML_DEMON_PARAMTEXT_H
