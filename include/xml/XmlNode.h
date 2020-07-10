//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLNODE_H
#define XML_DEMON_XMLNODE_H
#include <string>


struct XmlNode {
    std::string name;
    std::list<std::pair<std::string, std::string>> props;
    virtual ~XmlNode() = default;
};

struct XmlText : public XmlNode {
    std::string text;
    virtual ~XmlText() = default;
};
#endif //XML_DEMON_XMLNODE_H
