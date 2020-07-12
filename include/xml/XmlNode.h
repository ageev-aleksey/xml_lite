//
// Created by nrx on 10.07.2020.
//

#ifndef XML_DEMON_XMLNODE_H
#define XML_DEMON_XMLNODE_H
#include <string>
#include <unordered_map>

/**
 * @brief Данный узла дерева xml документа.
 */
struct XmlNode {
    std::string name; //< Название xml тега
    std::unordered_map<std::string, std::string> props; //< значение свойств xml тега
    virtual ~XmlNode() = default;
};

/**
 * @brief Текст внутри тела xml тега
 */
struct XmlText : public XmlNode {
    std::string text;
    virtual ~XmlText() = default;
};


#endif //XML_DEMON_XMLNODE_H
