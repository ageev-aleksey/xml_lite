//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_PARSER_H
#define XML_DEMON_PARSER_H

#include "xml/Graph.h"
#include "xml/Lexer.h"
#include "xml/XmlNode.h"

class Parser {
public:
    explicit Parser(Lexer lexer);
    Graph<XmlNode*> parse();
private:
    void parseDocument(Graph<XmlNode*>::Iterator& node);
    //void parseProlog(Graph<XmlNode*>::Iterator& node);
    void parseRoot(Graph<XmlNode*>::Iterator& node);
    void parseNode(Graph<XmlNode*>::Iterator& node);
    void parsePropertyList(std::list<std::pair<std::string, std::string>> &props);
    std::string parseValue();
    void parseBodyElementList(Graph<XmlNode*>::Iterator& node);

    Lexer lexer;
    Graph<XmlNode*> graph;
};



#endif //XML_DEMON_PARSER_H
