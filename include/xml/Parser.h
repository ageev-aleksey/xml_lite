//
// Created by nrx on 09.07.2020.
//

#ifndef XML_DEMON_PARSER_H
#define XML_DEMON_PARSER_H

#include "xml/Graph.h"
#include "xml/Lexer.h"
#include "xml/XmlNode.h"

/**
 * Парсер xml документа
 */
class Parser {
    struct GraphCleaner {
        void operator()(Graph<XmlNode*> *graph);
    };
public:
    using XmlGraph = Graph<XmlNode*>; //< Тип описывающий дерево xml документа
    using XmlGraphPtr = std::unique_ptr<XmlGraph, GraphCleaner>; //< Указатель на дерево xml документа
    /**
     * @param lexer - лексер возвращающий поток токенов
     */
    explicit Parser(Lexer lexer);
    /**
     * @brief выполнить разбор xml  докуменат и получить построенно дерево.
     * @return дерево xml  документа.
     */
    XmlGraphPtr parse();

private:
    void parseDocument(Graph<XmlNode*>::Iterator& node);
    void parseProlog(Graph<XmlNode*>::Iterator& node);
    void parseRoot(Graph<XmlNode*>::Iterator& node);
    void parseNode(Graph<XmlNode*>::Iterator& node);
    void parsePropertyList(std::unordered_map<std::string, std::string> &props);
    std::string parseValue();
    void parseBodyElementList(Graph<XmlNode*>::Iterator& node);



    Lexer lexer;
    XmlGraphPtr graph;
};



#endif //XML_DEMON_PARSER_H
