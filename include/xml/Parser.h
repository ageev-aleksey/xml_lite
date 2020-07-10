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
    using XmlGraph = Graph<XmlNode*>;
    explicit Parser(Lexer lexer);
    XmlGraph parse();
private:
    void parseDocument(Graph<XmlNode*>::Iterator& node);
    void parseProlog(Graph<XmlNode*>::Iterator& node);
    void parseRoot(Graph<XmlNode*>::Iterator& node);
    void parseNode(Graph<XmlNode*>::Iterator& node);
    void parsePropertyList(std::unordered_map<std::string, std::string> &props);
    std::string parseValue();
    void parseBodyElementList(Graph<XmlNode*>::Iterator& node);

    static void XmlGraphClear(XmlGraph *graph);

    Lexer lexer;
    XmlGraph graph;
};



#endif //XML_DEMON_PARSER_H
